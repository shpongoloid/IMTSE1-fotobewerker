/*
 * FotoScherm.cpp
 *
 *  Created on: 5 mrt. 2012
 *      Author: Niek
 */

#include "FotoScherm.hpp"

//globale variabelen voor breedte en hoogte van het scherm
int screenWidth;
int screenHeight;

// de grootte van de afbeelding
int imageSize = 150;

// hulp bool om het indrukken van de knoppen te verbeteren
bool touched = false;

// constructor
FotoScherm::FotoScherm()
{
	// het optiescherm
	this->optieScherm = new OptieScherm( this );

	// sla schermgrootte op in globale variabelen
	MAExtent screenSize = maGetScrSize();
	screenWidth = EXTENT_X( screenSize );
	screenHeight = EXTENT_Y( screenSize );

	// de font en de widgetskin instellen
	Font* font = new Font( RES_FONT );
	WidgetSkin* skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 3, 4, 3, 4, false, false );

	// label aanmaken
	Label* label = new Label( 0, 0, 0, 0, NULL );

	// een achtergrond label aanmaken
	this->achtergrondLabel = new Label( 0, 0, screenWidth, screenHeight, label, "", 0, font );
	this->achtergrondLabel->setBackgroundColor( 000055 );

	// een label maken waar de naam van de afbeelding op komt te staan
	this->imageTekst = new Label( ( screenWidth - imageSize ) / 2, (screenHeight - imageSize) / 2 + imageSize - 3, imageSize, 39, label, "Wheatly", 0, font );
	this->imageTekst->setPaddingLeft(6);
	this->imageTekst->setPaddingTop(10);
	this->imageTekst->setSkin( skin );

	// een button die je naar het optiescherm brengt
	this->button = new Label( ( screenWidth - 159 ) / 2, screenHeight - 50, 159, 39, label, "Open het optiescherm", 0, font );
	this->button->setPaddingLeft(6);
	this->button->setPaddingTop(10);
	this->button->setSkin( skin );

	// placeholder maken die de afbeelding bevat
	MAHandle tekening = maCreatePlaceholder();
	maCreateDrawableImage( tekening, 200, 200 );

	maSetDrawTarget( tekening );
	maSetColor( 0x555500 );
	maFillRect( 0, 0, 200, 200 );

	// drawtarget weer aan het scherm geven
	maSetDrawTarget( HANDLE_SCREEN );

	// het aanmaken van de afbeelding
	Image* tekenVeld = new Image( (screenWidth - imageSize) / 2, (screenHeight - imageSize) / 2, imageSize, imageSize, label, false, false, RES_IMAGE );
	tekenVeld->setSkin( skin );

	this->setMain( label );
}

// destructor
FotoScherm::~FotoScherm()
{
	// TODO Auto-generated destructor stub
}

// het laten zien en updaten van het fotoscherm
void FotoScherm::show()
{
	// roep de show() van de superklasse (Screen) aan
	this->Screen::show();

	// haal informatie imagetekst op van optiescherm
	this->imageTekst->setCaption( this->optieScherm->getImagetekst() );

	// haal informatie achtergrondkleur op van optiescherm
	this->achtergrondLabel->setBackgroundColor( this->optieScherm->getAchtergrondOptie() );

	// haal informatie grootte op van optiescherm
	imageSize = this->optieScherm->getGrootte();
}

// afvangen invoer
void FotoScherm::keyPressEvent(int keyCode, int nativeCode)
{
	// bij indrukken van de MAK_FIRE toets, laat optiescherm zien
	if( keyCode == MAK_FIRE )
	{
		this->optieScherm->show();
	}
}

// pressevent
void FotoScherm::pointerPressEvent(MAPoint2d point)
{
	if( this->button->contains( point.x, point.y ) )
	{
		this->button->setSelected( true );
		touched = true;
	}
	else
	{
		this->button->setSelected( false );
		touched = false;
	}
}

// releaseevent, ik gebruik dit om het klikken van de buttons te verbeteren, als je nu op de button klikt en er met de muis vanaf gaat en dan loslaat gebeurt er niks, normaal namelijk wel
void FotoScherm::pointerReleaseEvent(MAPoint2d point)
{
	if( this->button->contains( point.x, point.y ) && touched )
	{
		this->button->setSelected( false );
		this->optieScherm->show();
	}
	else
	{
		this->button->setSelected( false );
		touched = false;
	}
}
