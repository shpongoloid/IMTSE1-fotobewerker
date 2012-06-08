/*
 * FotoBewerker.cpp
 *
 *  Created on: 5 mrt. 2012
 *      Author: Niek
 */

#include "FotoBewerker.hpp"

// constructor, het fotoscherm laten zien
FotoBewerker::FotoBewerker()
{
	Screen* screen = new FotoScherm();
	screen->show();
}

// destructor
FotoBewerker::~FotoBewerker()
{
	// TODO Auto-generated destructor stub
}
