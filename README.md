# What is an Unmanned Ground Effect Vehicle (UGEV)?

  ![GEV](https://github.com/user-attachments/assets/28bee322-1f18-4b8f-84f4-bc3cf1ea138c)

Unmanned Ground Effect Vehicles (UGEVs), also called Ekranoplans, are autonomous craft that utilize an aerodynamic phenomenon which increases lift and decreases drag when flying just above the surface of water. Despite its increased flight efficiency, GEVs have been disregarded primarily due to challenges with craft stability and control. However, with the increasing development of autonomous systems, UGEVs offer new capabilities to improve the reliability and safety of this unique craft. Due to its high speed and low-detectability flight profile, applications of UGEVs include:
- Military reconnaissance
- Supply/personnel transport
- Mine laying/anti-mine warfare
- Antisubmarine warfare
- Surface warfare via strike and kamikaze tactics

However, there is limited research into autonomous multi-craft or multi-agent UGEV navigation. UGEV swarms have the potential to benefit from increased aerodynamic efficiency in formation flight, cooperative navigation through simultaneous localization and mapping (SLAM), as well as improved cost awareness and optimization. GEVs are impacted by many environmental factors such as inclement weather, waves, significant wind, land formations, and obstacles which hinder safety and impede efficient aerodynamic efficiency. The introduction of multi-agent UGEV navigation can help mitigate these hazards and improve the reliability of UGEVs.

# Multi-Agent UGEV Navigation

![Sim](https://github.com/user-attachments/assets/7c823cf7-5304-4c60-8615-e08a14356c3f)

Figure 1. Example simulation of multi-agent UGEV environment


<img width="228" height="880" alt="block_diagram" src="https://github.com/user-attachments/assets/f3988f8c-67a5-4248-90f9-a030430f7663" />

Figure 2. GEV Swarm system block diagram

# Build 
rm -rf build install log
colcon build --symlink-install --parallel-workers 4
source install/setup.bash
ros2 run my_agent environment_publisher

# Run
source install/setup.bash
ros2 launch my_agent multi_agent.launch.py
