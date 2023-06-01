#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "IntersectionSimulationClass.h"
#include "random.h"

//Programmer: Yi Zhou
//Date: 04/15/2022
//Purpose: defined three functions, did not change anything else
//The functions are scheduleArrival, scheduleLightChange, handleNextEvent.

void IntersectionSimulationClass::readParametersFromFile(
     const string &paramFname
     )
{
  bool success = true;;
  ifstream paramF;

  paramF.open(paramFname.c_str());

  //Check that the file was able to be opened...
  if (paramF.fail())
  {
    success = false;
    cout << "ERROR: Unable to open parameter file: " << paramFname << endl;
  }
  else
  {
    //Now read in all the params, according to the specified format of
    //the text-based parameter file.
    if (success)
    {
      paramF >> randomSeedVal;
      if (paramF.fail() ||
          randomSeedVal < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set random generatsor seed" << endl;
      }
    }

    if (success)
    {
      paramF >> timeToStopSim;
      if (paramF.fail() ||
          timeToStopSim <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set simulation end time" << endl;
      }
    }

    if (success)
    {
      paramF >> eastWestGreenTime >> eastWestYellowTime;
      if (paramF.fail() ||
          eastWestGreenTime <= 0 ||
          eastWestYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east-west times" << endl;
      }
    }

    if (success)
    {
      paramF >> northSouthGreenTime >> northSouthYellowTime;
      if (paramF.fail() ||
          northSouthGreenTime <= 0 ||
          northSouthYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north-south times" << endl;
      }
    }

    if (success)
    {
      paramF >> eastArrivalMean >> eastArrivalStdDev;
      if (paramF.fail() ||
          eastArrivalMean <= 0 ||
          eastArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> westArrivalMean >> westArrivalStdDev;
      if (paramF.fail() ||
          westArrivalMean <= 0 ||
          westArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set west arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> northArrivalMean >> northArrivalStdDev;
      if (paramF.fail() ||
          northArrivalMean <= 0 ||
          northArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> southArrivalMean >> southArrivalStdDev;
      if (paramF.fail() ||
          southArrivalMean <= 0 ||
          southArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set south arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> percentCarsAdvanceOnYellow;
      if (paramF.fail() || 
          percentCarsAdvanceOnYellow < 0 ||
          percentCarsAdvanceOnYellow > 100)
      {
        success = false;
        cout << "ERROR: Unable to read/set percentage yellow advance" << endl;
      }

      //Use the specified seed to seed the random number generator
      setSeed(randomSeedVal);
    }

    paramF.close();
  }

  //Let the caller know whether things went well or not by printing the
  if (!success)
  {
    cout << "ERROR: Parameter file was NOT read in successfully, so the " <<
            "simulation is NOT setup properly!" << endl;
    isSetupProperly = false;
  }
  else
  {
    cout << "Parameters read in successfully - simulation is ready!" << endl;
    isSetupProperly = true;
  }
}

void IntersectionSimulationClass::printParameters() const
{
  cout << "===== Begin Simulation Parameters =====" << endl;
  if (!isSetupProperly)
  {
    cout << "  Simulation is not yet properly setup!" << endl;
  }
  else
  {
    cout << "  Random generator seed: " << randomSeedVal << endl;
    cout << "  Simulation end time: " << timeToStopSim << endl;

    cout << "  East-West Timing -" <<
            " Green: " << eastWestGreenTime << 
            " Yellow: " << eastWestYellowTime <<
            " Red: " << getEastWestRedTime() << endl;

    cout << "  North-South Timing -" <<
            " Green: " << northSouthGreenTime << 
            " Yellow: " << northSouthYellowTime <<
            " Red: " << getNorthSouthRedTime() << endl;

    cout << "  Arrival Distributions:" << endl;
    cout << "    East - Mean: " << eastArrivalMean << 
            " StdDev: " << eastArrivalStdDev << endl;
    cout << "    West - Mean: " << westArrivalMean << 
            " StdDev: " << westArrivalStdDev << endl;
    cout << "    North - Mean: " << northArrivalMean << 
            " StdDev: " << northArrivalStdDev << endl;
    cout << "    South - Mean: " << southArrivalMean << 
            " StdDev: " << southArrivalStdDev << endl;

    cout << "  Percentage cars advancing through yellow: " <<
            percentCarsAdvanceOnYellow << endl;
  }
  cout << "===== End Simulation Parameters =====" << endl;
}




//The style for the following three functions are consistent with
//my own coding style.

//Impltemented function one
void IntersectionSimulationClass::scheduleArrival(
    const string &travelDir
) {
    EventClass eventToSchedule;
    int eventTypeDir = EVENT_UNKNOWN;
    int arrivalTime = 0;
    cout << "Time: " << currentTime << " Scheduled ";
    //set up arrival time and event type for the certain direction
    if (travelDir == EAST_DIRECTION) {
        arrivalTime = currentTime + 
        getPositiveNormal(eastArrivalMean, eastArrivalStdDev);
        eventTypeDir = EVENT_ARRIVE_EAST;
    }
    else if (travelDir == WEST_DIRECTION) {
        arrivalTime = currentTime + 
        getPositiveNormal(westArrivalMean, westArrivalStdDev);
        eventTypeDir = EVENT_ARRIVE_WEST;
    }
    else if (travelDir == NORTH_DIRECTION) {
        arrivalTime = currentTime + 
        getPositiveNormal(northArrivalMean, northArrivalStdDev);
        eventTypeDir = EVENT_ARRIVE_NORTH;
    }
    else if (travelDir == SOUTH_DIRECTION) {
        arrivalTime = currentTime + 
        getPositiveNormal(southArrivalMean, southArrivalStdDev);
        eventTypeDir = EVENT_ARRIVE_SOUTH;
    }
    //set up the event properly
    eventToSchedule = EventClass(arrivalTime, eventTypeDir);
    //insert it to the sorted list
    eventList.insertValue(eventToSchedule);
    cout << eventToSchedule << endl;
}





//Impltemented function one
void IntersectionSimulationClass::scheduleLightChange() {
    EventClass eventToSchedule;
    int eventTypeLight = EVENT_UNKNOWN;
    int eventTime = 0;
    cout << "Time: " << currentTime << " Scheduled ";
    //set up event time and event type for the light change
    if (currentLight == LIGHT_GREEN_EW) {
        eventTime = currentTime + eastWestGreenTime;
        eventTypeLight = EVENT_CHANGE_YELLOW_EW;
    }
    else if (currentLight == LIGHT_YELLOW_EW) {
        eventTime = currentTime + eastWestYellowTime;
        eventTypeLight = EVENT_CHANGE_GREEN_NS;
    }
    else if (currentLight == LIGHT_GREEN_NS) {
        eventTime = currentTime + northSouthGreenTime;
        eventTypeLight = EVENT_CHANGE_YELLOW_NS;
    }
    else if (currentLight == LIGHT_YELLOW_NS) {
        eventTime = currentTime + northSouthYellowTime;
        eventTypeLight = EVENT_CHANGE_GREEN_EW;
    }
    //set up the event properly
    eventToSchedule = EventClass(eventTime, eventTypeLight);
    //insert it to the sorted list
    eventList.insertValue(eventToSchedule);
    cout << eventToSchedule << endl;
}





//Impltemented function one
bool IntersectionSimulationClass::handleNextEvent() {
    //the boolean to return
    bool doKeepRunning = true;
    //the event to handle 
    EventClass eventToHandle;
    //stores the event that results from removefront, this is the 
    //event that we will handle
    eventList.removeFront(eventToHandle);
    //update current time
    currentTime = eventToHandle.getTimeOccurs();
    //if passed the time limit, do not handle the event and return false
    if (currentTime > timeToStopSim) {
        doKeepRunning = false;
        cout << endl;
        cout << "Next event occurs AFTER the simulation end time (" 
        << eventToHandle << ")!" << endl;
    }
    //within time limit, handle the event and return true
    else {
        doKeepRunning = true;
        cout << endl;
        cout << "Handling " << eventToHandle << endl;
        //event is car arrival
        //east
        if (eventToHandle.getType() == EVENT_ARRIVE_EAST) {
            //construct a new car and add it to the queue
            CarClass carInQueue(EAST_DIRECTION, currentTime);
            eastQueue.enqueue(carInQueue);
            cout << "Time: " << currentTime << " Car #" 
            << carInQueue.getId() << " arrives east-bound - queue length: " 
            << eastQueue.getNumElems() << endl;
            //schedule next arrival in this direction
            scheduleArrival(EAST_DIRECTION);
            //update statistics if needed
            int eastQueueLen = eastQueue.getNumElems();
            if (eastQueueLen > maxEastQueueLength) {
                maxEastQueueLength = eastQueueLen;
            }
        }
        //west
        else if (eventToHandle.getType() == EVENT_ARRIVE_WEST) {
            //construct a new car and add it to the queue
            CarClass carInQueue(WEST_DIRECTION, currentTime);
            westQueue.enqueue(carInQueue);
            cout << "Time: " << currentTime << " Car #" 
            << carInQueue.getId() << " arrives west-bound - queue length: " 
            << westQueue.getNumElems() << endl;
            //schedule next arrival in this direction
            scheduleArrival(WEST_DIRECTION);
            //update statistics if needed
            int westQueueLen = westQueue.getNumElems();
            if (westQueueLen > maxWestQueueLength) {
                maxWestQueueLength = westQueueLen;
            }
        }
        //north
        else if (eventToHandle.getType() == EVENT_ARRIVE_NORTH) {
            //construct a new car and add it to the queue
            CarClass carInQueue(NORTH_DIRECTION, currentTime);
            northQueue.enqueue(carInQueue);
            cout << "Time: " << currentTime << " Car #" 
            << carInQueue.getId() << " arrives north-bound - queue length: " 
            << northQueue.getNumElems() << endl;
            //schedule next arrival in this direction
            scheduleArrival(NORTH_DIRECTION);
            //update statistics if needed
            int northQueueLen = northQueue.getNumElems();
            if (northQueueLen > maxNorthQueueLength) {
                maxNorthQueueLength = northQueueLen;
            }
        }
        //south
        else if (eventToHandle.getType() == EVENT_ARRIVE_SOUTH) {
            //construct a new car and add it to the queue
            CarClass carInQueue(SOUTH_DIRECTION, currentTime);
            southQueue.enqueue(carInQueue);
            cout << "Time: " << currentTime << " Car #" 
            << carInQueue.getId() << " arrives south-bound - queue length: " 
            << southQueue.getNumElems() << endl;
            //schedule next arrival in this direction
            scheduleArrival(SOUTH_DIRECTION);
            //update statistics if needed
            int southQueueLen = southQueue.getNumElems();
            if (southQueueLen > maxSouthQueueLength) {
                maxSouthQueueLength = southQueueLen;
            }
        }
        //event is light change
        //change yellow ew
        else if (eventToHandle.getType() == EVENT_CHANGE_YELLOW_EW) {
            //change light
            currentLight = LIGHT_YELLOW_EW;
            cout << "Advancing cars on east-west green" << endl;
            int eastQueueLen = eastQueue.getNumElems();
            int westQueueLen = westQueue.getNumElems();
            int countEastAdvance = 0;
            int countWestAdvance = 0;
            //east
            //if no cars in queue
            if (eastQueueLen == 0) {
                cout << "  No east-bound cars waiting " 
                << "to advance on green" << endl;
            }
            //if #cars in queue is less than or equal to light duration
            else if (eastQueueLen <= eastWestGreenTime) {
                //let all cars advance
                for (int i = 1; i <= eastQueueLen; i++) {
                    //create a car to store the advanced car
                    CarClass carToAdvance;
                    //the car advances
                    eastQueue.dequeue(carToAdvance);
                    cout << "  Car #" << carToAdvance.getId()
                    << " advances east-bound" << endl;
                    //update number of cars advanced
                    countEastAdvance++;
                }
                //The commented lines are used to output information about
                //green lights.
                //However, the TA told us that we only need to output this
                //information for yellow lights.
                //I left it here in case the grader needs it to output info
                /*
                if (countEastAdvance < eastWestGreenTime) {
                    cout << "  No east-bound cars waiting " 
                    << "to advance on green" << endl;
                }
                */
            }
            //if #cars in queue is larger than light duration
            else if (eastQueueLen > eastWestGreenTime) {
                //let cars advance, but not all
                for (int i = 1; i <= eastWestGreenTime; i++) {
                    //create a car to store the advanced car
                    CarClass carToAdvance;
                    //the car advances
                    eastQueue.dequeue(carToAdvance);
                    cout << "  Car #" << carToAdvance.getId()
                    << " advances east-bound" << endl;
                    //update number of cars advanced
                    countEastAdvance++;
                }
            }
            numTotalAdvancedEast = numTotalAdvancedEast + countEastAdvance;
            //west
            //if no cars in queue
            if (westQueueLen == 0) {
                cout << "  No west-bound cars waiting " 
                << "to advance on green" << endl;
            }
            //if #cars in queue is less than or equal to light duration
            else if (westQueueLen <= eastWestGreenTime) {
                //let all cars advance
                for (int i = 1; i <= westQueueLen; i++) {
                    //create a car to store the advanced car
                    CarClass carToAdvance;
                    //the car advances
                    westQueue.dequeue(carToAdvance);
                    cout << "  Car #" << carToAdvance.getId()
                    << " advances west-bound" << endl;
                    //update number of cars advanced
                    countWestAdvance++;
                }
                //The commented lines are used to output information about
                //green lights.
                //However, the TA told us that we only need to output this
                //information for yellow lights.
                //I left it here in case the grader needs it to output info
                /*
                if (countWestAdvance < eastWestGreenTime) {
                    cout << "  No west-bound cars waiting " 
                    << "to advance on green" << endl;
                }
                */
            }
            //if #cars in queue is larger than light duration
            else if (westQueueLen > eastWestGreenTime) {
                //let cars advance, but not all
                for (int i = 1; i <= eastWestGreenTime; i++) {
                    //create a car to store the advanced car
                    CarClass carToAdvance;
                    //the car advances
                    westQueue.dequeue(carToAdvance);
                    cout << "  Car #" << carToAdvance.getId()
                    << " advances west-bound" << endl;
                    //update number of cars advanced
                    countWestAdvance++;
                }
            }
            numTotalAdvancedWest = numTotalAdvancedWest + countWestAdvance;
            //print information
            cout << "East-bound cars advanced on green: " << countEastAdvance
            << " Remaining queue: " << eastQueue.getNumElems() << endl;
            cout << "West-bound cars advanced on green: " << countWestAdvance
            << " Remaining queue: " << westQueue.getNumElems() << endl;
            //schedule next light change
            scheduleLightChange();           
        }
        //change yellow ns
        else if (eventToHandle.getType() == EVENT_CHANGE_YELLOW_NS) {
            //change light
            currentLight = LIGHT_YELLOW_NS;
            cout << "Advancing cars on north-south green" << endl;
            int northQueueLen = northQueue.getNumElems();
            int southQueueLen = southQueue.getNumElems();
            int countNorthAdvance = 0;
            int countSouthAdvance = 0;
            //north
            //if no cars in queue
            if (northQueueLen == 0) {
                cout << "  No north-bound cars waiting " 
                << "to advance on green" << endl;
            }
            //if #cars in queue is less than or equal to light duration
            else if (northQueueLen <= northSouthGreenTime) {
                //let all cars advance
                for (int i = 1; i <= northQueueLen; i++) {
                    //create a car to store the advanced car
                    CarClass carToAdvance;
                    //the car advances
                    northQueue.dequeue(carToAdvance);
                    cout << "  Car #" << carToAdvance.getId()
                    << " advances north-bound" << endl;
                    //update number of cars advanced
                    countNorthAdvance++;
                }
                //The commented lines are used to output information about
                //green lights.
                //However, the TA told us that we only need to output this
                //information for yellow lights.
                //I left it here in case the grader needs it to output info
                /*
                if (countNorthAdvance < northSouthGreenTime) {
                    cout << "  No north-bound cars waiting " 
                    << "to advance on green" << endl;
                }
                */
            }
            //if #cars in queue is larger than light duration
            else if (northQueueLen > northSouthGreenTime) {
                //let cars advance, but not all
                for (int i = 1; i <= northSouthGreenTime; i++) {
                    //create a car to store the advanced car
                    CarClass carToAdvance;
                    //the car advances
                    northQueue.dequeue(carToAdvance);
                    cout << "  Car #" << carToAdvance.getId()
                    << " advances north-bound" << endl;
                    //update number of cars advanced
                    countNorthAdvance++;
                }
            }
            numTotalAdvancedNorth = numTotalAdvancedNorth + countNorthAdvance;
            //south
            //if no cars in queue
            if (southQueueLen == 0) {
                cout << "  No south-bound cars waiting " 
                << "to advance on green" << endl;
            }
            //if #cars in queue is less than or equal to light duration
            else if (southQueueLen <= northSouthGreenTime) {
                //let all cars advance
                for (int i = 1; i <= southQueueLen; i++) {
                    //create a car to store the advanced car
                    CarClass carToAdvance;
                    //the car advances
                    southQueue.dequeue(carToAdvance);
                    cout << "  Car #" << carToAdvance.getId()
                    << " advances south-bound" << endl;
                    //update number of cars advanced
                    countSouthAdvance++;
                }
                //The commented lines are used to output information about
                //green lights.
                //However, the TA told us that we only need to output this
                //information for yellow lights.
                //I left it here in case the grader needs it to output info
                /*
                if (countSouthAdvance < northSouthGreenTime) {
                    cout << "  No south-bound cars waiting " 
                    << "to advance on green" << endl;
                }
                */
            }
            //if #cars in queue is larger than light duration
            else if (southQueueLen > northSouthGreenTime) {
                //let cars advance, but not all
                for (int i = 1; i <= northSouthGreenTime; i++) {
                    //create a car to store the advanced car
                    CarClass carToAdvance;
                    //the car advances
                    southQueue.dequeue(carToAdvance);
                    cout << "  Car #" << carToAdvance.getId()
                    << " advances south-bound" << endl;
                    //update number of cars advanced
                    countSouthAdvance++;
                }
            }
            numTotalAdvancedSouth = numTotalAdvancedSouth + countSouthAdvance;
            //print information
            cout << "North-bound cars advanced on green: " << countNorthAdvance
            << " Remaining queue: " << northQueue.getNumElems() << endl;
            cout << "South-bound cars advanced on green: " << countSouthAdvance
            << " Remaining queue: " << southQueue.getNumElems() << endl;
            //schedule next light change
            scheduleLightChange();           
        }
        //change green ns
        else if (eventToHandle.getType() == EVENT_CHANGE_GREEN_NS) {
            //change light
            currentLight = LIGHT_GREEN_NS;
            cout << "Advancing cars on east-west yellow" << endl;
            int eastQueueLen = eastQueue.getNumElems();
            int westQueueLen = westQueue.getNumElems();
            int countEastAdvance = 0;
            int countWestAdvance = 0;
            //east
            //if no cars in queue
            if (eastQueueLen == 0) {
                cout << "  No east-bound cars waiting " 
                << "to advance on yellow" << endl;
            }
            //if cars in queue
            else {
                //if the percent for a drive to advance is 0,
                //do not do anything and go to cout
                //This if may seem a bit duplicated, but it corresponds to the
                //the first sample text file. Allows me to debug.
                //Also, this saves time when the possibility is actually zero
                if (percentCarsAdvanceOnYellow == 0) {
                    cout << "  Next east-bound car will NOT advance on yellow"
                    << endl;
                }
                //when the possibility is not zero
                else {
                    bool doAdvance = true;
                    while (doAdvance && countEastAdvance <= 
                    eastWestYellowTime) {
                        //if no cars left in queue
                        if (eastQueue.getNumElems() == 0) {
                            cout << "  No east-bound cars waiting " 
                            << "to advance on yellow" << endl;
                            doAdvance = false;
                        }
                        //if cars left in queue
                        else {
                            int chance = getUniform(1, 100);
                            //if advance
                            if (chance <= percentCarsAdvanceOnYellow) {
                                //create a car to store the advanced car
                                CarClass carToAdvance;
                                //the car advances
                                eastQueue.dequeue(carToAdvance);
                                cout << "  Next east-bound car will "
                                << "advance on yellow" << endl;
                                cout << "  Car #" << carToAdvance.getId()
                                << " advances east-bound" << endl;
                                //update number of cars advanced
                                countEastAdvance++;
                            }
                            //if not advance
                            else {
                                doAdvance = false;
                                cout << "  Next east-bound car will NOT "
                                <<"advance on yellow" << endl;
                            }
                        }
                    }

                }

            }
            numTotalAdvancedEast = numTotalAdvancedEast + countEastAdvance;
            //west
            //if no cars in queue
            if (westQueueLen == 0) {
                cout << "  No west-bound cars waiting " 
                << "to advance on yellow" << endl;
            }
            //if cars in queue
            else {
                //if the percent for a drive to advance is 0,
                //do not do anything and go to cout
                //This if may seem a bit duplicated, but it corresponds to the
                //the first sample text file. Allows me to debug.
                //Also, this saves time when the possibility is actually zero
                if (percentCarsAdvanceOnYellow == 0) {
                    cout << "  Next west-bound car will NOT advance on yellow"
                    << endl;
                }
                //when the possibility is not zero
                else {
                    bool doAdvance = true;
                    while (doAdvance && countWestAdvance <= 
                    eastWestYellowTime) {
                        //if no cars left in queue
                        if (westQueue.getNumElems() == 0) {
                            cout << "  No west-bound cars waiting " 
                            << "to advance on yellow" << endl;
                            doAdvance = false;
                        }
                        //if cars left in queue
                        else {
                            int chance = getUniform(1, 100);
                            //if advance
                            if (chance <= percentCarsAdvanceOnYellow) {
                                //create a car to store the advanced car
                                CarClass carToAdvance;
                                //the car advances
                                westQueue.dequeue(carToAdvance);
                                cout << "  Next west-bound car will "
                                << "advance on yellow" << endl;
                                cout << "  Car #" << carToAdvance.getId()
                                << " advances west-bound" << endl;
                                //update number of cars advanced
                                countWestAdvance++;
                            }
                            //if not advance
                            else {
                                doAdvance = false;
                                cout << "  Next west-bound car will NOT "
                                <<"advance on yellow" << endl;
                            }
                        }
                    }

                }

            }
            numTotalAdvancedWest = numTotalAdvancedWest + countWestAdvance;
            //print information
            cout << "East-bound cars advanced on yellow: " << countEastAdvance
            << " Remaining queue: " << eastQueue.getNumElems() << endl;
            cout << "West-bound cars advanced on yellow: " << countWestAdvance
            << " Remaining queue: " << westQueue.getNumElems() << endl;
            //schedule next light change
            scheduleLightChange(); 
        }
        //change green ew
        else if (eventToHandle.getType() == EVENT_CHANGE_GREEN_EW) {
            //change light
            currentLight = LIGHT_GREEN_EW;
            cout << "Advancing cars on north-south yellow" << endl;
            int northQueueLen = northQueue.getNumElems();
            int southQueueLen = southQueue.getNumElems();
            int countNorthAdvance = 0;
            int countSouthAdvance = 0;
            //north
            //if no cars in queue
            if (northQueueLen == 0) {
                cout << "  No north-bound cars waiting " 
                << "to advance on yellow" << endl;
            }
            //if cars in queue
            else {
                //if the percent for a drive to advance is 0,
                //do not do anything and go to cout
                //This if may seem a bit duplicated, but it corresponds to the
                //the first sample text file. Allows me to debug.
                //Also, this saves time when the possibility is actually zero
                if (percentCarsAdvanceOnYellow == 0) {
                    cout << "  Next north-bound car will NOT advance on yellow"
                    << endl;
                }
                //when the possibility is not zero
                else {
                    bool doAdvance = true;
                    while (doAdvance && countNorthAdvance <= 
                    northSouthYellowTime) {
                        //if no cars left in queue
                        if (northQueue.getNumElems() == 0) {
                            cout << "  No north-bound cars waiting " 
                            << "to advance on yellow" << endl;
                            doAdvance = false;
                        }
                        //if cars left in queue
                        else {
                            int chance = getUniform(1, 100);
                            //if advance
                            if (chance <= percentCarsAdvanceOnYellow) {
                                //create a car to store the advanced car
                                CarClass carToAdvance;
                                //the car advances
                                northQueue.dequeue(carToAdvance);
                                cout << "  Next north-bound car will "
                                << "advance on yellow" << endl;
                                cout << "  Car #" << carToAdvance.getId()
                                << " advances north-bound" << endl;
                                //update number of cars advanced
                                countNorthAdvance++;
                            }
                            //if not advance
                            else {
                                doAdvance = false;
                                cout << "  Next north-bound car will NOT "
                                <<"advance on yellow" << endl;
                            }
                        }
                    }

                }

            }
            numTotalAdvancedNorth = numTotalAdvancedNorth + countNorthAdvance;
            //south
            //if no cars in queue
            if (southQueueLen == 0) {
                cout << "  No south-bound cars waiting " 
                << "to advance on yellow" << endl;
            }
            //if cars in queue
            else {
                //if the percent for a drive to advance is 0,
                //do not do anything and go to cout
                //This if may seem a bit duplicated, but it corresponds to the
                //the first sample text file. Allows me to debug.
                //Also, this saves time when the possibility is actually zero
                if (percentCarsAdvanceOnYellow == 0) {
                    cout << "  Next south-bound car will NOT advance on yellow"
                    << endl;
                }
                //when the possibility is not zero
                else {
                    bool doAdvance = true;
                    while (doAdvance && countSouthAdvance <= 
                    northSouthYellowTime) {
                        //if no cars left in queue
                        if (southQueue.getNumElems() == 0) {
                            cout << "  No south-bound cars waiting " 
                            << "to advance on yellow" << endl;
                            doAdvance = false;
                        }
                        //if cars left in queue
                        else {
                            int chance = getUniform(1, 100);
                            //if advance
                            if (chance <= percentCarsAdvanceOnYellow) {
                                //create a car to store the advanced car
                                CarClass carToAdvance;
                                //the car advances
                                southQueue.dequeue(carToAdvance);
                                cout << "  Next south-bound car will "
                                << "advance on yellow" << endl;
                                cout << "  Car #" << carToAdvance.getId()
                                << " advances south-bound" << endl;
                                //update number of cars advanced
                                countSouthAdvance++;
                            }
                            //if not advance
                            else {
                                doAdvance = false;
                                cout << "  Next south-bound car will NOT "
                                <<"advance on yellow" << endl;
                            }
                        }
                    }

                }

            }
            numTotalAdvancedSouth = numTotalAdvancedSouth + countSouthAdvance;
            //print information
            cout << "North-bound cars advanced on yellow: " 
            << countNorthAdvance
            << " Remaining queue: " << northQueue.getNumElems() << endl;
            cout << "South-bound cars advanced on yellow: " 
            << countSouthAdvance
            << " Remaining queue: " << southQueue.getNumElems() << endl;
            //schedule next light change
            scheduleLightChange(); 
        }

    }
    return doKeepRunning;
}





void IntersectionSimulationClass::printStatistics(
     ) const
{
  cout << "===== Begin Simulation Statistics =====" << endl;
  cout << "  Longest east-bound queue: " << maxEastQueueLength << endl;
  cout << "  Longest west-bound queue: " << maxWestQueueLength << endl;
  cout << "  Longest north-bound queue: " << maxNorthQueueLength << endl;
  cout << "  Longest south-bound queue: " << maxSouthQueueLength << endl;
  cout << "  Total cars advanced east-bound: " <<
          numTotalAdvancedEast << endl;
  cout << "  Total cars advanced west-bound: " <<
          numTotalAdvancedWest << endl;
  cout << "  Total cars advanced north-bound: " <<
          numTotalAdvancedNorth << endl;
  cout << "  Total cars advanced south-bound: " <<
          numTotalAdvancedSouth << endl;
  cout << "===== End Simulation Statistics =====" << endl;
}
