#ifndef __MSECTION_H__
#define __MSECTION_H__
#include "Section.h"

class MSection : public Section{
private:
    Section *north;    
    Section *east;      
    Section *west;    
    Section *south;     

public:
    MSection();  
    ~MSection();

    Section *getNext() override;   
    Section *getLast() override;   
    Section *getRight();         

    // Inline get and set methods for directions;
    inline Section *getNorth(){ return north; } 
    inline Section *getEast(){ return east; }  
    inline Section *getSouth(){ return south; } 
    inline Section *getWest(){ return west; }      
    inline void setNorth(Section *north){ this->north = north; }    
    inline void setEast(Section *east){ this->east = east; }        
    inline void setSouth(Section *south){ this->south = south; }    
    inline void setWest(Section *west){ this->west = west; }    
};

#endif
