# Adventure Bot: A Tale of Exploration

Welcome to the Adventure Bot project, an engaging simulation where a persistent robot navigates through a dynamic landscape filled with unexpected obstacles and shifting targets. This project is more than just a display of technological prowess; it's a narrative on curiosity, adaptability, and the joy of discovery. Just like a true explorer, our robot, dubbed the Adventurer, seeks out new destinations, each representing a newfound knowledge or experience, demonstrating that the journey itself is the ultimate adventure.

## Inspiration

Drawing from the spirit of exploration that drives us to seek out the unknown, the Adventure Bot embodies the essence of discovery. In this dynamic world, obstacles represent the challenges we face in our quest for knowledge, and the ever-moving target points symbolize the evolving nature of our goals and aspirations. This project serves as a metaphor for the continuous pursuit of learning and growth, emphasizing that change is the only constant in the journey of life.

## Mechanics

Utilizing the robust frameworks provided by [Elma](https://github.com/klavinslab/elma) and [Enviro](https://github.com/klavinslab/enviro), this interactive simulation features a robot equipped with the intelligence to overcome barriers and pursue objectives that dynamically appear within its environment. Additionally, users can guide the Adventurer by setting new goals directly within the map, offering a hands-on experience in shaping the robot's path of exploration.

![Adventure Bot Exploration](images/adventure_bot_exploration.gif)

## Key Features

- **Dynamic Exploration**: The Adventurer robot tirelessly navigates through the environment, showcasing the thrill of exploration.
- **Interactive Objectives**: Users can influence the robot's journey by designating new target points on the map, illustrating the power of direction and purpose.
- **Intelligent Obstacle Avoidance**: Equipped with sensors, the robot adeptly maneuvers around barriers, symbolizing the importance of overcoming challenges in the pursuit of discovery.
- **Renewable Goals**: As soon as one target is reached, another appears, reflecting the endless pursuit of knowledge and experience.

## Getting Started

### Prerequisites

Make sure Docker and Git are installed on your system:

1. [Docker](https://docs.docker.com/get-docker/)
2. [Git](https://git-scm.com/)

### Installation Guide

1. Open your terminal.
2. Clone the Adventure Bot repository:
   ```bash
   git clone https://github.com/Skymore/520-Assignments.git
   ```
3. Navigate to the project directory:
   ```bash
   cd 520-Assignments/Final_Project/project
   ```
4. Start the Docker image (adjust `$PWD` to your project's path if necessary):
   ```bash
   docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.5 bash
   ```
5. Initiate the project:
   ```bash
   esm start
   enviro
   ```
6. Visit localhost in your web browser to join the Adventurer in its exploration.

## Key Challenges and Solutions

Throughout the development of the Adventure Bot project, we encountered several significant challenges that required creative solutions:

### Static Agents Limitation

**Challenge**: Initially, agents within our environment were static, which posed a limitation as they could not move or change positions. This restriction was particularly problematic for simulating a dynamic environment where the robot needed to interact with movable objects.

**Solution**: To overcome this limitation, we transitioned our agents from static to dynamic entities and assigned them a very high mass.

### Obstacle Navigation

**Challenge**: The robot occasionally struggled to navigate around obstacles, getting stuck in certain situations. This issue detracted from the smoothness of the exploration experience and needed to be addressed.

**Solution**: We implemented a mechanism to automatically adjust the positions of obstacles every five seconds. This dynamic alteration of the environment ensures that if the robot finds itself unable to bypass an obstacle, it won't remain stuck indefinitely. Instead, the changing landscape presents new pathways and challenges, encouraging continuous exploration and problem-solving.

## Acknowledgements

The development of Adventure Bot is made possible thanks to the foundational tools [Elma](https://github.com/klavinslab/elma) and [Enviro](https://github.com/klavinslab/enviro) by [Klavins Lab](https://github.com/klavinslab). A heartfelt thank you to everyone who finds inspiration in the Adventurer's exploration, reminding us of the endless possibilities that await when we embrace the journey of discovery.