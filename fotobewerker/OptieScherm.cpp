/*
 * OptieScherm.cpp
 *
 *  Created on: 3 mrt. 2012
 *      Author: Niek
 */

#include "OptieScherm.hpp"

int screenWidther;
int screenHeighter;
bool toucher;

// constructor
OptieScherm::OptieScherm( Screen* parent )
{
	// sla parent scherm op (FotoScherm) om de show() te kunnen aanroepen, zodat dit optiescherm weer gesloten wordt
	this->parent = parent;

	// bepaal grootte van het scherm
	MAExtent screenSize = maGetScrSize();
	screenWidther = EXTENT_X( screenSize );
	screenHeighter = EXTENT_Y( screenSize );

	// standaard font en grafisch uiterlijk (uit de resource file res.lst)
	Font* font = new MAUI::Font(RES_FONT);
	WidgetSkin* skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 3, 4, 3, 4, false, false );

	// maak een label die andere widgets straks bevat, en een achtergrondkleur heeft
	Label* label = new Label( 0, 0, 0, 0, NULL );

	// stel achtergrondkleur in
	label->setBackgroundColor( 0x9cd7eb );

	achtergrondKleur = 000000;

	// tijdens het toevoegen van knoppen bewerk ik ook de padding, zodat de tekst in de knoppen er mooier uitzien
	// maak rode knop en voeg hem toe aan de vector
	this->roodLabel = new Label(( screenWidther - 50 ) / 2, 80, 50, 39, label, "Rood", 0, font);
	this->roodLabel->setPaddingLeft( 9 );
	this->roodLabel->setPaddingTop( 10 );
	roodLabel->setSkin( skin );
	this->kleurLabels.add( roodLabel );

	// maak groene knop en voeg hem toe aan de vector
	this->groenLabel = new Label(( screenWidther - 50 - 120 ) / 2, 80, 50, 39, label, "Groen", 0, font);
	this->groenLabel->setPaddingLeft( 6 );
	this->groenLabel->setPaddingTop( 10 );
	groenLabel->setSkin( skin );
	this->kleurLabels.add( groenLabel );

	// maak blauwe knop en voeg hem toe aan de vector
	this->blauwLabel = new Label(( screenWidther - 50 + 120 ) / 2, 80, 50, 39, label, "Blauw", 0, font);
	this->blauwLabel->setPaddingLeft( 6 );
	this->blauwLabel->setPaddingTop( 10 );
	blauwLabel->setSkin( skin );
	this->kleurLabels.add( blauwLabel );

	// stel grootte plaatje in m.b.v. editbox
	this->editBoxGrootte = new EditBox( ( screenWidther - 100 ) / 2, 140, 60, 39, label, "150", 0, font, true, false, 20 );
	this->editBoxGrootte->setPaddingLeft( 6 );
	this->editBoxGrootte->setPaddingTop( 10 );
	this->editBoxGrootte->setCursorColor( 0x3a5009 );
	this->editBoxGrootte->setSkin( skin );

	// stel naam plaatje in m.b.v. editbox
	this->editBox = new EditBox( ( screenWidther - 200 ) / 2, 20, 200, 39, label, "Wheatly", 0, font, true, false, 20 );
	this->editBox->setPaddingLeft( 6 );
	this->editBox->setPaddingTop( 10 );
	this->editBox->setCursorColor( 0x3a5009 );
	this->editBox->setSkin( skin );

	// keer terug naar de foto en sla de bewerkingen op
	this->imageTekst = new Label( ( screenWidther - 168 ) / 2, screenHeighter - 50, 168, 39, label, "Keer terug naar de foto", 0, font );
	this->imageTekst->setPaddingLeft( 6 );
	this->imageTekst->setPaddingTop( 10 );
	this->imageTekst->setSkin( skin );

	this->setMain( label );
}

OptieScherm::~OptieScherm()
{
	// verwijder objecten van deze klasse
}


// geef ingestelde achtergrondkleur terug
int OptieScherm::getAchtergrondOptie()
{
	// geef de juiste achtergrondkleur bij de int
	if( achtergrondKleur == 100 )
		return 0xff0000;
	else if( achtergrondKleur == 010 )
		return 0x00ff00;
	else
		return 0x0000ff;
}

// geef ingestelde imagetekst van de editbox terug
const BasicString<char> OptieScherm::getImagetekst()
{
	return this->editBox->getCaption(); // caption is de text in een editbox
}

// geef ingestelde grootte van de editbox terug
int OptieScherm::getGrootte()
{
	return 150;
	// return this->editBoxGrootte->getCaption(); //caption is de text in een editbox
}

// terugkeren naar het fotoscherm bij het indrukken van de MAK_FIRE toets
void OptieScherm::keyPressEvent(int keyCode, int nativeCode)
{
	if( keyCode == MAK_FIRE )
	{
		this->parent->show();
	}
}

// pointerpressevent
void OptieScherm::pointerPressEvent(MAPoint2d point)
{
	if( this->imageTekst->contains( point.x, point.y ) )
	{
		this->imageTekst->setSelected( true );
		toucher = true;
	}
	else
	{
		this->imageTekst->setSelected( false );
		toucher = false;
	}

	// behandel de editbox bij selecteren (touch), verander de editBox naar je eigen editbox(en)
	if( this->editBox->contains( point.x, point.y ) )
	{
		this->editBox->setSelected( true );
	}
	else
	{
		this->editBox->setSelected( false );
	}

	if( this->editBoxGrootte->contains( point.x, point.y ) )
		{
			this->editBoxGrootte->setSelected( true );
		}
		else
		{
			this->editBoxGrootte->setSelected( false );
		}

	// doorloop alle kleurlabels om selectie in te stellen
	for( int i = 0; i < this->kleurLabels.size(); i++ )
	{
		if( this->kleurLabels[i]->contains( point.x, point.y ) )
		{
			this->kleurLabels[i]->setSelected( true );

			if( kleurLabels[i]->getCaption() == "Rood" )
			{
				achtergrondKleur = 100;
			}
			else if( kleurLabels[i]->getCaption() == "Groen" )
			{
				achtergrondKleur = 010;
			}
			else if( kleurLabels[i]->getCaption() == "Blauw" )
			{
				achtergrondKleur = 001;
			}

		}
		else
		{
			this->kleurLabels[i]->setSelected( false );
		}
	}
}

// zelfde verhaal als bij fotoscherm.cpp
void OptieScherm::pointerReleaseEvent(MAPoint2d point)
{
	if( this->imageTekst->contains( point.x, point.y ) && toucher )
	{
		this->imageTekst->setSelected( false );

		this->parent->show();
	}
	else
	{
		this->imageTekst->setSelected( false );
		toucher = false;
	}
}
