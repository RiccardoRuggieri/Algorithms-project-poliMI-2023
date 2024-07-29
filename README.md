# Algorithms project poliMi-2023

This project involves planning the most efficient route between two expressway stations, minimizing stops. It prioritizes shorter distances from the expressway's start and avoiding duplicate routes. Grade: 30/30 cum laude.

## Introduction

This project revolves around the optimization of travel routes between service stations on an expressway. It is aimed at minimizing the number of stops between two stations while also giving preference to routes with shorter distances from the expressway's starting point. Furthermore, the project seeks to avoid duplicate routes, ensuring that each route is uniquely identified by its sequence of service stations.

## Expressway and Service Stations

- The expressway is conceptualized as a series of service stations.
- Each service station is situated at a specific distance, measured in kilometers from the expressway's starting point, denoted by a non-negative integer.
- There are no duplicate distances; hence, each service station is uniquely identified by its distance from the expressway's origin.

## Electric Vehicle Rentals

- Each service station is equipped with a fleet of electric rental vehicles.
- These vehicles are defined by their battery charge range, measured in kilometers and expressed as a positive integer.
- The maximum capacity of electric vehicles at a single station is 512.
- When renting a vehicle at station ```s```, it is possible to reach any station within the vehicle's range.

## Journeys and Stops

- A journey is represented as a sequence of service stations where the driver makes stops.
- The journey commences at one service station and concludes at another, with the possibility of passing through zero or more intermediate stations.
- Drivers are not allowed to backtrack during the journey, and a new vehicle must be rented at each station stop.
- Consequently, for two consecutive stops ```s``` and ```t```, ```t``` must always be farther from the starting point than ```s```, and ```t``` must be reachable using one of the available vehicles at ```s```.

## Project Objective

The main objective of this project is to plan routes with the fewest stops between two given stations. In cases where multiple routes have an identical minimum number of stops, the project aims to select the route that gives preference to stops with shorter distances from the expressway's origin.

## Route Selection Criteria

In cases of routes with an equal number of stops, the criteria for selection are as follows:

- Consider the set of n tied routes, denoted as ```P = {p1, p2, ..., pn}.```
- Each route is a tuple of m elements, with ```pi = ⟨pi,1, pi,2, ..., pi,m⟩``` representing the distances from the expressway's origin for each stop in the order of the route.
- The unique route pi should be chosen such that no other route pj exists with the same k final stops followed by a stop with a shorter distance. Formally,
  ```∄j, k: ⟨pi,m-k+1, ..., pi,m⟩ = ⟨pj,m-k+1, ..., pj,m⟩ and pj,m-k < pi,m-k.```

This project aims to address the challenges of expressway route planning while adhering to the stated objectives and criteria.

## Usage

To use the route planning system, detailed instructions will be provided in the associated code and documentation.

## Contributors

- Riccardo Ruggieri

## Acknowledgment

The project was held under the supervision of professor Davide Martinenghi in the context of the algorithms and data structures course at Polytechnic of Milan.
