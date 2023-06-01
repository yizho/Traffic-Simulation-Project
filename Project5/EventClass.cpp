#include <iostream>
using namespace std;

#include "EventClass.h"
#include "constants.h"

//Programmer: Yi Zhou
//Date: 04/15/2022
//Purpose: overloaded two operators, did not change anything else

ostream& operator<<(
     ostream& outStream,
     const EventClass &eventToPrint
     )
{
  outStream << "Event Type: ";
  if (eventToPrint.typeId == EVENT_ARRIVE_EAST)
  {
    outStream << "East-Bound Arrival";
  }
  else if (eventToPrint.typeId == EVENT_ARRIVE_WEST)
  {
    outStream << "West-Bound Arrival";
  }
  else if (eventToPrint.typeId == EVENT_ARRIVE_NORTH)
  {
    outStream << "North-Bound Arrival";
  }
  else if (eventToPrint.typeId == EVENT_ARRIVE_SOUTH)
  {
    outStream << "South-Bound Arrival";
  }
  else if (eventToPrint.typeId == EVENT_CHANGE_GREEN_EW)
  {
    outStream << "Light Change to EW Green";
  }
  else if (eventToPrint.typeId == EVENT_CHANGE_YELLOW_EW)
  {
    outStream << "Light Change to EW Yellow";
  }
  else if (eventToPrint.typeId == EVENT_CHANGE_GREEN_NS)
  {
    outStream << "Light Change to NS Green";
  }
  else if (eventToPrint.typeId == EVENT_CHANGE_YELLOW_NS)
  {
    outStream << "Light Change to NS Yellow";
  }
  else
  {
    outStream << "UNKNOWN";
  }
  outStream << " Time: " << eventToPrint.timeOccurs;
  return outStream;
}


bool EventClass::operator < (
    const EventClass &eventToCompare
) const {
    return (timeOccurs < eventToCompare.timeOccurs);
}

bool EventClass::operator >= (
    const EventClass &eventToCompare
) const {
    return (timeOccurs >= eventToCompare.timeOccurs);
}
