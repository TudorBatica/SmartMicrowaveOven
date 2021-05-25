[Raport de Analiza](https://docs.google.com/document/d/19thVfuHb2temk63EOPdjzD1iz0EYRSH4JCCTqInNfOI/edit?usp=sharing)  
# SmartMicrowaveOven
![CI workflow badge](https://github.com/TudorBatica/SmartMicrowaveOven/workflows/Build/badge.svg)  
API that simulates a smart microwave oven.    

## Getting Started
### Prerequisites
Building this project requires:
  - C++ compiler (to use the makefile you need g++)
  - [Pistache](http://pistache.io/docs/#installing-pistache) (C++ REST Framework)
### Build and Run
  - Build using `make`.  
  - Run with `./main`.  
  - App starts listening at `http://localhost:9080`.

## Usage
### Presets
Presets allow the user to store predefined jobs for different foods.
#### Retrieve all presets
`GET /presets`
#### Add a preset
`POST /presets/:jobtype/:food/:duration/:power`

### Commands
A user can choose an existing preset to run after some amount of time.
#### Retrieve all commands
`GET /commands`
#### Add a command
`POST /commands/:time/:presetId`

### Automatically generated jobs
The smart microwave can generate a job automatically. To do so, it either uses a preset or it computes the job using as input the food's weight.  
`GET /generateJob/:food/:jobType/:weight`

