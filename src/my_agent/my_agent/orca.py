import numpy as np
from typing import Tuple, List, Dict, Optional


class ORCAAvoidance:

    def __init__(self, time_horizon: float = 1.5, agent_radius: float = 0.5):
        self.time_horizon = time_horizon
        self.agent_radius = agent_radius
    
    def compute_velocity(
        self,
        agent_pos: Tuple[int, int],
        desired_vel: Tuple[float, float],
        neighbors: Dict[int, Tuple[int, int]],
        neighbor_vels: Optional[Dict[int, Tuple[float, float]]] = None,
        max_speed: float = 1.0
    ) -> Tuple[float, float]:
        if not neighbors:
            # No neighbors, use desired velocity directly
            return self._clamp_velocity(desired_vel, max_speed)
        
        # Initialize with desired velocity
        new_velocity = np.array(desired_vel, dtype=float)
        
        # Build ORCA constraints for each neighbor
        constraints = []
        
        for neighbor_id, neighbor_pos in neighbors.items():
            # Get neighbor velocity (default to zero if not available)
            neighbor_vel = neighbor_vels.get(neighbor_id, (0.0, 0.0)) if neighbor_vels else (0.0, 0.0)
            
            constraint = self._compute_orca_constraint(
                agent_pos,
                new_velocity,
                neighbor_pos,
                neighbor_vel
            )
            
            if constraint is not None:
                constraints.append(constraint)
        
        # If no constraints, use desired velocity
        if not constraints:
            return self._clamp_velocity(new_velocity, max_speed)
        
        # Find best velocity satisfying all constraints
        new_velocity = self._find_best_velocity(
            desired_vel,
            constraints,
            max_speed
        )
        
        return tuple(new_velocity)
    
    def _compute_orca_constraint(
        self,
        agent_pos: np.ndarray,
        agent_vel: np.ndarray,
        neighbor_pos: np.ndarray,
        neighbor_vel: np.ndarray
    ) -> Optional[Tuple[np.ndarray, float]]:
        agent_pos = np.array(agent_pos, dtype=float)
        neighbor_pos = np.array(neighbor_pos, dtype=float)
        agent_vel = np.array(agent_vel, dtype=float)
        neighbor_vel = np.array(neighbor_vel, dtype=float)
        
        # Relative position and velocity
        relative_pos = agent_pos - neighbor_pos
        relative_vel = agent_vel - neighbor_vel
        
        dist_sq = np.dot(relative_pos, relative_pos)
        min_sep = 2.0 * self.agent_radius
        
        # Check if collision is possible
        if dist_sq >= min_sep * min_sep:
            a = np.dot(relative_vel, relative_vel)
            if a < 1e-10:
                # Zero relative velocity: agents moving identically, no collision predicted.
                # Guard also prevents divide-by-zero at line below (RuntimeWarning source).
                return None

            b = 2.0 * np.dot(relative_pos, relative_vel)
            c = dist_sq - min_sep * min_sep

            discriminant = b * b - 4 * a * c

            if discriminant < 0:
                return None

            tau = min(self.time_horizon, (-b - np.sqrt(discriminant)) / (2 * a))
            if tau < 0:
                return None
        else:
            # Already in collision, use time horizon
            tau = self.time_horizon
        
        # Compute ORCA constraint
        # The half-plane is the set of velocities that avoid collision
        w_prime = relative_pos + tau * relative_vel
        w_prime_mag = np.linalg.norm(w_prime)
        
        if w_prime_mag == 0:
            w_prime = np.array([1.0, 0.0])
            w_prime_mag = 1.0
        
        # Normal to the half-plane (perpendicular to w_prime)
        u = w_prime / w_prime_mag
        n = np.array([-u[1], u[0]])  # Rotate 90 degrees
        
        # Offset for the half-plane
        # Agents should maintain separation of min_sep
        offset = min_sep / tau if tau > 0 else min_sep
        
        return (n, offset)
    
    def _find_best_velocity(
        self,
        desired_vel: Tuple[float, float],
        constraints: List[Tuple[np.ndarray, float]],
        max_speed: float
    ) -> np.ndarray:
        desired = np.array(desired_vel, dtype=float)
        desired_normalized = desired / (np.linalg.norm(desired) + 1e-6)
        
        # Start with desired velocity clamped to max speed
        best_vel = desired_normalized * min(np.linalg.norm(desired), max_speed)
        
        # Try to satisfy constraints while staying close to desired
        for normal, offset in constraints:
            # Check if current velocity violates constraint
            val = np.dot(best_vel, normal)
            
            if val < offset:
                # Violates constraint, project onto boundary
                # Move velocity so it's on the constraint boundary
                best_vel = best_vel + (offset - val) * normal
        
        # Clamp final velocity to max speed
        return self._clamp_velocity(best_vel, max_speed)
    
    def _clamp_velocity(self, velocity: np.ndarray, max_speed: float) -> np.ndarray:
        vel_mag = np.linalg.norm(velocity)
        if vel_mag > max_speed:
            return velocity / vel_mag * max_speed
        return velocity


def orca_grid_move(
    current_pos: Tuple[int, int],
    desired_direction: Tuple[float, float],
    neighbors: Dict[int, Tuple[int, int]],
    neighbor_velocities: Dict[int, Tuple[float, float]],
    grid_height: int,
    grid_width: int,
    orca: ORCAAvoidance
) -> Tuple[int, int]:
    i, j = current_pos
    
    # Compute safe velocity using ORCA
    safe_vel = orca.compute_velocity(
        current_pos,
        desired_direction,
        neighbors,
        neighbor_velocities,
        max_speed=1.0
    )
    
    # Convert continuous velocity to discrete grid move
    # Try all 8 neighbors and pick the one closest to safe velocity
    candidates = [
        (i-1, j-1), (i-1, j), (i-1, j+1),
        (i, j-1),   (i, j),   (i, j+1),
        (i+1, j-1), (i+1, j), (i+1, j+1)
    ]
    
    best_move = (i, j)
    best_score = float('inf')
    
    for ni, nj in candidates:
        # Bounds check
        if ni < 0 or ni >= grid_height or nj < 0 or nj >= grid_width:
            continue
        
        # Movement vector
        move_vel = np.array([ni - i, nj - j], dtype=float)
        
        # Score: deviation from ORCA velocity
        deviation = np.linalg.norm(move_vel - safe_vel)
        
        if deviation < best_score:
            best_score = deviation
            best_move = (ni, nj)
    
    return best_move
