#ifndef __SECTION_H__
#define __SECTION_H__

#include <string>
#include "VehicleBase.h"

class Section{
private:
    Section *next;      // Next Section
    Section *last;      // Previous Section
    bool empty;         
    VehicleBase *vehicle = nullptr;    

protected:
    bool middle = false;   

public:
    Section();
   virtual ~Section();
    Section(const Section& other);
    Section& operator=(const Section& other);
    Section(Section&& other)noexcept;
    Section& operator=(Section&& other)noexcept;

    void Remove();                 
    void putVehicle(VehicleBase *);    

    virtual inline Section *getNext(){ return next; }   // get next Section
    virtual inline Section *getLast(){ return last; }   // get last Section
    virtual inline bool isMiddle(){ return middle; }    // returns true if the section is a MSection
    inline bool isEmpty(){ return empty; }              // return true if Section is empty
    inline void setNext(Section *section){ next = section; }    // Set the next Section
    inline void setLast(Section *section){ last = section; }    // Set the last Section
    inline VehicleBase *getVehicle(){ return vehicle; } // Get VehicleBase on this Section

};

#endif