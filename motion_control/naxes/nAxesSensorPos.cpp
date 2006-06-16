// $Id: nAxisGeneratorCartesianPos.hpp,v 1.1.1.1 2003/12/02 20:32:06 kgadeyne Exp $
// Copyright (C) 2003 Klaas Gadeyne <klaas.gadeyne@mech.kuleuven.ac.be>
//                    Wim Meeussen  <wim.meeussen@mech.kuleuven.ac.be>
// Copyright (C) 2006 Ruben Smits <ruben.smits@mech.kuleuven.be>
//  
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//  
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//  
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//  

#include "nAxesSensorPos.hpp"
#include <corelib/Logger.hpp>
#include <assert.h>

namespace Orocos
{
  using namespace RTT;
  using namespace std;
  
  nAxesSensorPos::nAxesSensorPos(string name,unsigned int num_axes)
    : GenericTaskContext(name),
      _num_axes(num_axes), 
      _position_local(num_axes),
      _position_sensors(num_axes),
      _position_naxes("nAxesSensorPosition")
  {
    
    for(int i=0;i<_num_axes;i++){
      char buf[80];
      sprintf(buf,"positionValue%d",i);
      _position_sensors[i] = new ReadDataPort<double>(buf);
      ports()->addPort(_position_sensors[i]);
    }
    
    ports()->addPort(&_position_naxes);
  }
  
  nAxesSensorPos::~nAxesSensorPos(){};
  
  bool nAxesSensorPos::startup()
  {
    //initialize values
    Logger::log()<<Logger::Debug<<"nAxesSensorPos: Initial position: ";
    for (unsigned int i=0; i<_num_axes; i++){
      _position_local[i] = _position_sensors[i]->Get();
      Logger::log()<<_position_local[i]<<Logger::endl;
    }
    _position_naxes.Set(_position_local);
    
    return true;
  }
  
  
  void nAxesSensorPos::update()
  {
    // copy values from position sensors to local variable
    for (unsigned int i=0; i<_num_axes; i++)
      _position_local[i] = _position_sensors[i]->Get();
    
    _position_naxes.Set(_position_local);
  }
  
  void nAxesSensorPos::shutdown()
  {
  }
  
}//namespace

