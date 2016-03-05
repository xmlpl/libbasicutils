/*******************************************************************\

              Copyright (C) 2004 Joseph Coffland

    This program is free software; you can redistribute it and/or
     modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
        of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
             GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
     along with this program; if not, write to the Free Software
      Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
                           02111-1307, USA.

            For information regarding this software email
                   jcofflan@users.sourceforge.net

\*******************************************************************/
#ifndef BASICFUNCTOR_H
#define BASICFUNCTOR_H

struct BasicFunctorBase {
	virtual ~BasicFunctorBase() {}
  virtual void operator()()=0;
};

template <class T>
struct BasicFunctor : public BasicFunctorBase {
  void (T::*fpt)();   // pointer to member function
  T* pt2Object;  // pointer to object

  public:
  BasicFunctor(T* _pt2Object, void(T::*_fpt)())
  {pt2Object = _pt2Object;  fpt = _fpt;};
	virtual ~BasicFunctor() {}

  virtual void operator()() {(*pt2Object.*fpt)();}
};
#endif // BASICFUNCTOR_H
