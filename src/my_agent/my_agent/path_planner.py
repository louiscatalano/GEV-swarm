import heapq
import numpy as np
from typing import Tuple, List, Dict, Optional


class DStarLite:

    def __init__(self, height: int, width: int):
        self.height = height
        self.width = width
        self.U = []       # Priority queue — lazy deletion; may contain stale entries
        self.U_tag = {}   # u -> version counter; stale heap entries have an old version
        self.rhs = {}
        self.g = {}
        self.km = 0
        self.start = None
        self.goal = None
        self.last_start = None
        self.cost_map = np.ones((height, width))
        self.old_cost_map = np.ones((height, width))

    def heuristic(self, s1: Tuple[int, int], s2: Tuple[int, int]) -> float:
        return np.sqrt((s1[0] - s2[0])**2 + (s1[1] - s2[1])**2)

    def calculate_key(self, s: Tuple[int, int]) -> Tuple[float, float]:
        min_val = min(self.g.get(s, float('inf')), self.rhs.get(s, float('inf')))
        return (min_val + self.heuristic(self.start, s) + self.km, min_val)

    def get_neighbors(self, s: Tuple[int, int]) -> List[Tuple[int, int]]:
        i, j = s
        return [
            (i + di, j + dj)
            for di in [-1, 0, 1]
            for dj in [-1, 0, 1]
            if (di != 0 or dj != 0) and 0 <= i + di < self.height and 0 <= j + dj < self.width
        ]

    def cost(self, s1: Tuple[int, int], s2: Tuple[int, int]) -> float:
        cell_cost = self.cost_map[s2[0], s2[1]]
        if not np.isfinite(cell_cost):
            return float('inf')
        di, dj = abs(s2[0] - s1[0]), abs(s2[1] - s1[1])
        return (np.sqrt(2) if di + dj == 2 else 1.0) * cell_cost

    def update_vertex(self, u: Tuple[int, int]):
        # Lazy deletion: bump version + push new entry instead of removing old one
        # (O(log n) vs O(n)). Matters when hundreds of cells change per step.
        if u != self.goal:
            self.rhs[u] = min(
                self.cost(u, s) + self.g.get(s, float('inf'))
                for s in self.get_neighbors(u)
            )
        self.U_tag[u] = self.U_tag.get(u, 0) + 1
        if self.g.get(u, float('inf')) != self.rhs.get(u, float('inf')):
            heapq.heappush(self.U, (self.calculate_key(u), u, self.U_tag[u]))

    def compute_shortest_path(self):
        while self.U:
            k_old, u, tag = self.U[0]
            if tag != self.U_tag.get(u, 0):
                heapq.heappop(self.U)
                continue
            k_start = self.calculate_key(self.start)
            if k_old >= k_start and self.g.get(self.start, float('inf')) == self.rhs.get(self.start, float('inf')):
                break
            heapq.heappop(self.U)
            k_new = self.calculate_key(u)
            if k_old < k_new:
                self.U_tag[u] = self.U_tag.get(u, 0) + 1
                heapq.heappush(self.U, (k_new, u, self.U_tag[u]))
            elif self.g.get(u, float('inf')) > self.rhs.get(u, float('inf')):
                self.g[u] = self.rhs[u]
                for s in self.get_neighbors(u):
                    self.update_vertex(s)
            else:
                self.g[u] = float('inf')
                self.update_vertex(u)
                for s in self.get_neighbors(u):
                    self.update_vertex(s)

    def initialize(self, start: Tuple[int, int], goal: Tuple[int, int], cost_map: np.ndarray):
        self.start = start
        self.goal = goal
        self.last_start = start
        self.cost_map = cost_map.copy()
        self.old_cost_map = cost_map.copy()
        self.U = []
        self.U_tag = {}
        self.rhs = {}
        self.g = {}
        self.km = 0
        self.rhs[self.goal] = 0
        self.U_tag[self.goal] = 1
        heapq.heappush(self.U, (self.calculate_key(self.goal), self.goal, 1))
        self.compute_shortest_path()

    def replan(self, new_start: Tuple[int, int], cost_map: np.ndarray) -> Optional[List[Tuple[int, int]]]:
        self.km += self.heuristic(self.last_start, new_start)
        self.last_start = new_start
        self.start = new_start

        changed_cells = [
            (i, j)
            for i in range(self.height)
            for j in range(self.width)
            if not np.isclose(self.old_cost_map[i, j], cost_map[i, j], rtol=0.01, equal_nan=True)
        ]

        for cell in changed_cells:
            self.cost_map[cell[0], cell[1]] = cost_map[cell[0], cell[1]]
            for neighbor in self.get_neighbors(cell):
                self.update_vertex(neighbor)
            self.update_vertex(cell)

        self.old_cost_map = cost_map.copy()
        self.compute_shortest_path()
        return self.extract_path()

    def extract_path(self) -> Optional[List[Tuple[int, int]]]:
        if self.g.get(self.start, float('inf')) == float('inf'):
            return None
        path = [self.start]
        current = self.start
        for _ in range(self.height * self.width):
            if current == self.goal:
                break
            best_next = min(
                self.get_neighbors(current),
                key=lambda n: self.cost(current, n) + self.g.get(n, float('inf')),
                default=None
            )
            if best_next is None or self.cost(current, best_next) + self.g.get(best_next, float('inf')) == float('inf'):
                return None
            path.append(best_next)
            current = best_next
        return path

    def plan(self, start: Tuple[int, int], goal: Tuple[int, int], cost_map: np.ndarray) -> Optional[List[Tuple[int, int]]]:
        self.initialize(start, goal, cost_map)
        return self.extract_path()


class PotentialField:

    def __init__(self, k_att: float = 1.0, k_rep: float = 100.0, d0: float = 3.0):
        self.k_att = k_att
        self.k_rep = k_rep
        self.d0 = d0
        self.goal = None

    def attractive_force(self, pos: np.ndarray, goal: np.ndarray) -> np.ndarray:
        diff = goal - pos
        dist = np.linalg.norm(diff)
        return np.zeros(2) if dist < 0.1 else self.k_att * diff / dist

    def repulsive_force(self, pos: np.ndarray, obstacles: List[np.ndarray]) -> np.ndarray:
        force = np.zeros(2)
        for obs in obstacles:
            diff = pos - obs
            dist = np.linalg.norm(diff)
            if 0.1 < dist < self.d0:
                magnitude = self.k_rep * (1.0/dist - 1.0/self.d0) / dist**2
                force += magnitude * (diff / dist)
        return force

    def get_obstacles_in_range(self, pos: np.ndarray, cost_map: np.ndarray, range_dist: float) -> List[np.ndarray]:
        obstacles = []
        pi, pj = int(pos[0]), int(pos[1])
        r = int(np.ceil(range_dist))
        for i in range(max(0, pi - r), min(cost_map.shape[0], pi + r + 1)):
            for j in range(max(0, pj - r), min(cost_map.shape[1], pj + r + 1)):
                if not np.isfinite(cost_map[i, j]) or cost_map[i, j] > 0.7:
                    obstacles.append(np.array([i, j], dtype=float))
        return obstacles

    def plan(self, start: Tuple[int, int], goal: Tuple[int, int], cost_map: np.ndarray, max_steps: int = 100) -> Optional[List[Tuple[int, int]]]:
        self.goal = goal
        pos = np.array(start, dtype=float)
        goal_arr = np.array(goal, dtype=float)
        path = [tuple(pos.astype(int))]
        for _ in range(max_steps):
            obstacles = self.get_obstacles_in_range(pos, cost_map, self.d0)
            f_total = self.attractive_force(pos, goal_arr) + self.repulsive_force(pos, obstacles)
            force_mag = np.linalg.norm(f_total)
            if force_mag < 1e-6:
                break
            pos += 0.5 * f_total / force_mag
            pos[0] = np.clip(pos[0], 0, cost_map.shape[0] - 1)
            pos[1] = np.clip(pos[1], 0, cost_map.shape[1] - 1)
            pos_int = tuple(pos.astype(int))
            if pos_int != path[-1]:
                path.append(pos_int)
            if np.linalg.norm(pos - goal_arr) < 1.0:
                break
        return path if np.linalg.norm(pos - goal_arr) <= 2.0 else None

    def replan(self, new_start: Tuple[int, int], cost_map: np.ndarray) -> Optional[List[Tuple[int, int]]]:
        return self.plan(new_start, self.goal, cost_map)
