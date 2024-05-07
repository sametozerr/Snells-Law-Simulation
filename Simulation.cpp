#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <math.h>
#include <string> 

#define VACUUM "Hava"
#define WATER "Su"
#define SAPPHIRE "Safir"
#define OLIVEOIL "Zeytinyaðý"
#define DIAMOND "Elmas"

#define PI 3.14

using namespace std;

double angleToRadian(float angle) 
{
	return (angle * PI) / 180;
}

float radianToAngle(float rad) 
{
	return (rad * 180) / PI;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(300, 300), "Snell's Law", sf::Style::Fullscreen);
    
    window.setFramerateLimit(60);
    
    // Kýrýlma Ýndisleri
    float n1;
    float n2;
    
    // Gelme açýsý ve kýrýlma açýþý
    float angleOfIncidence;
	float angleOfRefraction;
	
	// Geliþ hýzý ve gidiþ hýzý
	float speedOfIncidence;
	float speedOfRefraction;
	
	// Kýrýlma açýsýnýn sinüsü
	float sineOfRefraction;
	
	// Kritik açý
    float critAngle;
	
	int fCurrentMedia;
	int sCurrentMedia;
	
	// Ortamlar
	string medias[5] = {VACUUM, WATER, SAPPHIRE, OLIVEOIL, DIAMOND};
	
	// Birinci ve ikinci ortam
	string firstMedia;
	string secondMedia;
	
	std::map<std::string, float> indicesOfMedias;
	// std::map<std::string, float> lightSpeedOnMedias;
	
	// Bazý ortamlarýn kýrýlma indisleri
	indicesOfMedias[VACUUM] = 1;
	indicesOfMedias[WATER] = 1.333;
	indicesOfMedias[SAPPHIRE] = 1.77;
	indicesOfMedias[OLIVEOIL] = 1.47;
	indicesOfMedias[DIAMOND] = 2.417;
	
	/* Bazý ortamlarda ýþýðýn hýzý
	lightSpeedOnMedias[VACUUM] = 300;
	lightSpeedOnMedias[WATER] = 225.056;
	lightSpeedOnMedias[SAPPHIRE] = 169.492;
	lightSpeedOnMedias[OLIVEOIL] = 204.082;
	lightSpeedOnMedias[DIAMOND] = 124.121;
	*/
	
	// Deðer atama bölümü
	
	fCurrentMedia = 1;
	sCurrentMedia = 0;
	
	firstMedia = medias[fCurrentMedia];
	secondMedia = medias[sCurrentMedia];
	
	n1 = indicesOfMedias[medias[fCurrentMedia]];
	n2 = indicesOfMedias[medias[sCurrentMedia]];
	
	angleOfIncidence = 55;
	angleOfRefraction = radianToAngle( asin( (n1 / n2) * sin(angleToRadian(angleOfIncidence)) ) );
	
	// Asal ve normal eksenleri
	sf::RectangleShape principalAxis, normal, incidentRay, refractedRay, reflectedRay;
	sf::RectangleShape bcUp, bcDown;
	
	bcUp.setSize(sf::Vector2f( window.getSize().x, window.getSize().y / 2 ));
	bcUp.setPosition(sf::Vector2f(0, 0));
	bcUp.setFillColor(sf::Color(15,94,156));
	
	bcDown.setSize(sf::Vector2f( window.getSize().x, window.getSize().y / 2 ));
	bcDown.setPosition(sf::Vector2f(0, window.getSize().y /2));
	bcDown.setFillColor(sf::Color(153,217,255));

	principalAxis.setSize(sf::Vector2f( window.getSize().x, 10 ));
	principalAxis.setOrigin(sf::Vector2f(0 , principalAxis.getSize().y / 2));
	principalAxis.setPosition(sf::Vector2f(0, window.getSize().y /2 ));
	
	normal.setSize(sf::Vector2f( 10, window.getSize().y ));
	normal.setOrigin(sf::Vector2f(normal.getSize().x / 2 , 0));
	normal.setPosition(sf::Vector2f(window.getSize().x /2,  0));
	
	incidentRay.setSize(sf::Vector2f( 5, normal.getSize().y / 2 + 100.f));
	incidentRay.setOrigin(sf::Vector2f(incidentRay.getSize().x / 2, incidentRay.getSize().y));
	incidentRay.setPosition(sf::Vector2f(window.getSize().x / 2,  window.getSize().y / 2));
	incidentRay.setFillColor(sf::Color::Red);
	incidentRay.setRotation(-angleOfIncidence);
	
	refractedRay.setSize(sf::Vector2f( 5 ,normal.getSize().y / 2 + 100.f));
	refractedRay.setOrigin(sf::Vector2f(incidentRay.getSize().x / 2, 0));
	refractedRay.setPosition(sf::Vector2f(window.getSize().x / 2,  window.getSize().y / 2));
	refractedRay.setFillColor(sf::Color::Red);
	refractedRay.setRotation(-angleOfRefraction);
	
	reflectedRay.setSize(sf::Vector2f( 5 , normal.getSize().y / 2 + 100.f));
	reflectedRay.setOrigin(sf::Vector2f(reflectedRay.getSize().x / 2, reflectedRay.getSize().y));
	reflectedRay.setPosition(sf::Vector2f(window.getSize().x / 2,  window.getSize().y / 2));
	reflectedRay.setFillColor(sf::Color(255, 0, 0, 150));
	reflectedRay.setRotation(angleOfIncidence);
	
	sf::Font font;
	
	font.loadFromFile("tr_arial.ttf");
	
	sf::Text angleOfIncidence_t, angleOfRefraction_t, f_media, s_media, n1_t, n2_t, critAngle_t;
	sf::Text principalAxis_t, normal_t;
	
	angleOfIncidence_t.setFont(font);
	angleOfIncidence_t.setCharacterSize(50);
	angleOfIncidence_t.setPosition(sf::Vector2f(window.getSize().x - 450.f, 20.f));
	angleOfIncidence_t.setString("Gelme Açýsý = " + to_string( int(angleOfIncidence)) + "°");
	
	angleOfRefraction_t.setFont(font);
	angleOfRefraction_t.setCharacterSize(50);
	angleOfRefraction_t.setPosition(sf::Vector2f(window.getSize().x - 450.f, 90.f));
	angleOfRefraction_t.setString("Kýrýlma Açýsý = " + to_string( int(angleOfRefraction)) + "°");
	
	f_media.setFont(font);
	f_media.setCharacterSize(50);
	f_media.setPosition(sf::Vector2f(50.f,400.f));
	f_media.setString(firstMedia);
	f_media.setFillColor(sf::Color::Black);	
	
	s_media.setFont(font);
	s_media.setCharacterSize(50);
	s_media.setPosition(sf::Vector2f(50.f,600.f));
	s_media.setString(secondMedia);	
	s_media.setFillColor(sf::Color::Black);	
	
	n1_t.setFont(font);
	n1_t.setCharacterSize(30);
	// n1_t.setPosition(sf::Vector2f(25.f, 15.f));
	n1_t.setPosition(sf::Vector2f(75.f, 400.f + 75.f));
	n1_t.setFillColor(sf::Color::Black);	
	
	n2_t.setFont(font);
	n2_t.setCharacterSize(30);
	// n2_t.setPosition(sf::Vector2f(25.f, 65.f));
	n2_t.setPosition(sf::Vector2f(75.f, 600.f + 75.f));
	n2_t.setFillColor(sf::Color::Black);
	
	critAngle_t.setFont(font);
	critAngle_t.setCharacterSize(30);
	critAngle_t.setPosition(sf::Vector2f(window.getSize().x - 220.f, window.getSize().y / 2 + 20.f));
	
	principalAxis_t.setFont(font);
	principalAxis_t.setCharacterSize(30);
	principalAxis_t.setPosition(sf::Vector2f(window.getSize().x - 220.f, window.getSize().y / 2 - 50.f));
	principalAxis_t.setString("Asal Eksen");	
	principalAxis_t.setFillColor(sf::Color::Black);	
	
	normal_t.setFont(font);
	normal_t.setCharacterSize(30);
	normal_t.setPosition(sf::Vector2f(window.getSize().x / 2 + 50.f, 20));
	normal_t.setString("Normal");	
	normal_t.setFillColor(sf::Color::Black);	
	normal_t.setRotation(90);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
                
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				
 				if(sf::Mouse::getPosition(window).y < 530) 
				{
					if(fCurrentMedia < 4)
			 			fCurrentMedia++;
					else
						fCurrentMedia = 0;	 	
					}
 				
 					else 
					{
					if(sCurrentMedia < 4)
			 			sCurrentMedia++;
					else
						sCurrentMedia = 0;
					} 
			}    
        }
		
		
        if(medias[fCurrentMedia] == VACUUM) 
		{
			bcUp.setFillColor(sf::Color(15,94,156));
			f_media.setString(VACUUM);
			n1 = indicesOfMedias[VACUUM];	
		}
			
		else if(medias[fCurrentMedia] == WATER) 
		{
			bcUp.setFillColor(sf::Color(153,217,255));	
			f_media.setString(WATER);	
			n1 = indicesOfMedias[WATER];	
		}
			
		else if(medias[fCurrentMedia] == SAPPHIRE) 
		{
			bcUp.setFillColor(sf::Color(15,82,186));
			f_media.setString(SAPPHIRE);
			n1 = indicesOfMedias[SAPPHIRE];			
		}
			
		else if(medias[fCurrentMedia] == OLIVEOIL) 
		{
			bcUp.setFillColor(sf::Color(95,114,15));
			f_media.setString(OLIVEOIL);
			n1 = indicesOfMedias[OLIVEOIL];			
		}
			
		else 
		{
			bcUp.setFillColor(sf::Color(154,197,219));	
			f_media.setString(DIAMOND);	
			n1 = indicesOfMedias[DIAMOND];	
		}
		
		//////////////////////////////////////////////
		//////////////////////////////////////////////
		//////////////////////////////////////////////
		
		if(medias[sCurrentMedia] == VACUUM) 
		{
			bcDown.setFillColor(sf::Color(15,94,156));
			s_media.setString(VACUUM);
			n2 = indicesOfMedias[VACUUM];	
		}
			
		else if(medias[sCurrentMedia] == WATER) 
		{
			bcDown.setFillColor(sf::Color(153,217,255));	
			s_media.setString(WATER);
			n2 = indicesOfMedias[WATER];	
		}
			
		else if(medias[sCurrentMedia] == SAPPHIRE) 
		{
			bcDown.setFillColor(sf::Color(15,82,186));
			s_media.setString(SAPPHIRE);	
			n2 = indicesOfMedias[SAPPHIRE];	
		}
			
		else if(medias[sCurrentMedia] == OLIVEOIL) 
		{
			bcDown.setFillColor(sf::Color(95,114,15));
			s_media.setString(OLIVEOIL);
			n2 = indicesOfMedias[OLIVEOIL];		
		}
			
		else 
		{
			bcDown.setFillColor(sf::Color(154,197,219));	
			s_media.setString(DIAMOND);	
			n2 = indicesOfMedias[DIAMOND];
		}	

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
    		incidentRay.rotate(-1);
    		angleOfIncidence++;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
    		incidentRay.rotate(1);
    		angleOfIncidence--;	
		}
		
		if(n1 <= n2) 
		{
			angleOfRefraction = radianToAngle( asin( (n1 / n2) * sin(angleToRadian(angleOfIncidence)) ) );
			
		 	refractedRay.setRotation(-angleOfRefraction);
			
			reflectedRay.setRotation(angleOfIncidence);	
			
			reflectedRay.setFillColor(sf::Color(255, 0, 0, 150));	
		}
		
		else 
		{
			angleOfRefraction = radianToAngle(asin( (n1 / n2) * sin(angleToRadian(angleOfIncidence))));
			
			sineOfRefraction = (n1 / n2) * sin(angleToRadian(angleOfIncidence));
			
			critAngle = radianToAngle( asin( (n2 / n1) ) );
			
			reflectedRay.setRotation(angleOfIncidence);
			refractedRay.setRotation(-angleOfRefraction);
			
			if(sineOfRefraction > 1) 
			{
				reflectedRay.setFillColor(sf::Color::Red);
			}
			
			else 
			{
				reflectedRay.setFillColor(sf::Color(255, 0, 0, 150));	
			}
							
		}
			
		angleOfIncidence_t.setString("Gelme Açýsý = " + to_string( int(angleOfIncidence)) + "°");
		
		if(!(sineOfRefraction > 1 && n1 > n2)) 	
			angleOfRefraction_t.setString("Kýrýlma Açýsý = " + to_string( int(angleOfRefraction)) + "°");
		else
			angleOfRefraction_t.setString("Kýrýlma Açýsý = Yok");
			
		n1_t.setString("n1 = " + to_string(n1));		
		n2_t.setString("n2 = " + to_string(n2));
		
		critAngle_t.setString("Kritik açý = " + to_string(int(critAngle)) + "°");
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
    		window.close();	
		}

        window.clear();
        window.draw(bcUp);
        window.draw(bcDown);
        window.draw(principalAxis);
        window.draw(normal);
        window.draw(incidentRay);
        
        if(!(sineOfRefraction > 1 && n1 > n2)) 
        	window.draw(refractedRay);
        else {}
        	 
        window.draw(reflectedRay);
        window.draw(angleOfIncidence_t);
        window.draw(angleOfRefraction_t);
        window.draw(f_media);
        window.draw(s_media);
        window.draw(n1_t);
        window.draw(n2_t);
        window.draw(principalAxis_t);
		window.draw(normal_t);
        if(n1 > n2)
        	window.draw(critAngle_t);
        
        window.display();
    }

    return 0;
}					
