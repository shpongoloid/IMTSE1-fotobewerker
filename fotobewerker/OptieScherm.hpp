/*
* OptieScherm.hpp
*
* Created on: 3 mrt. 2012
* Author: Niek
*/

#ifndef OPTIESCHERM_HPP_
#define OPTIESCHERM_HPP_


#include <MAUTIL/Moblet.h>
#include <MAUI/Screen.h>
#include <MAUI/Label.h>
#include <MAUI/EditBox.h>
#include <MAUI/ListBox.h>
#include <MAUTIL/Vector.h>

#include "conprint.h"

#include "MAHeaders.h"

using namespace MAUtil;
using namespace MAUI;


class OptieScherm : public Screen
{
	private:
		Screen* parent;

		Vector<Label*> kleurLabels;
		Label* roodLabel;
		Label* groenLabel;
		Label* blauwLabel;
		Label* imageTekst;
		EditBox* editBox;
		EditBox* editBoxGrootte;

	public:
		OptieScherm( Screen* parent );
		virtual ~OptieScherm();

		void keyPressEvent(int keyCode, int nativeCode);
		void pointerPressEvent(MAPoint2d point);
		void pointerReleaseEvent(MAPoint2d point);

		int achtergrondKleur;
		int getAchtergrondOptie();
		int getGrootte();
		const BasicString<char>getImagetekst(); //geeft text van editbox terug
};

#endif /* OPTIESCHERM_HPP_ */
