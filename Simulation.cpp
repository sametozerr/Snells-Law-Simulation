#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <string> 

#define PI 3.14
#define numberOfMedias 5	

using namespace std;
 
enum Medias 
{
	Air,
	Water,
	Sapphire,
	Oliveoil,
	Diamond	
};

inline Medias operator++ (Medias & media) 
{	
	if(int(media) < numberOfMedias)
    	media = static_cast<Medias>((static_cast<int>(media) + 1) % numberOfMedias);	
}

inline Medias operator-- (Medias & media) 
{	
	if(int(media) > 0)
    	media = static_cast<Medias>((static_cast<int>(media) - 1));
    else 
	    media = static_cast<Medias>(static_cast<int>(numberOfMedias - 1));	
}

float getRefractiveIndex(Medias * media) 
{
	switch(*media)
	{
		case 0: return 1.00f; break;
		             
	    case 1: return 1.33f; break;
		
	    case 2: return 1.77f; break;
		
	    case 3: return 1.44f; break;
		
	    case 4: return 2.42f; break;		
	    		
	    default: 			 break;
	}
}

string getNameOfTheMedia(Medias * media) 
{
	
	switch(*media)
	{
		case 0: return "Air"; break;
		             
	    case 1: return "Water"; break;
		
	    case 2: return "Sapphire"; break;
		
	    case 3: return "Olive oil"; break;
		
	    case 4: return "Diamond"; break;		
	    		
	    default: 			 break;
	}	
}

sf::Color getBcColor(Medias * media) 
{
	switch(*media)
	{
		case 0: return sf::Color(15,94,156); break;
		             
	    case 1: return sf::Color(153,217,255); break;
		
	    case 2: return sf::Color(15,82,186); break;
		
	    case 3: return sf::Color(95,114,15); break;
		
	    case 4: return sf::Color(154,197,219); break;		
	    		
	    default: 			 break;
	}
		
}

double angleToRadian(float angle) { return (angle * PI) / 180; }
float radianToAngle(float rad) { return (rad * 180) / PI;}

int main()
{
    sf::RenderWindow window(sf::VideoMode(300, 300), "Snell's Law", sf::Style::Fullscreen);
    
    window.setFramerateLimit(60);
    
    // Kýrýlma indisleri
    float n1;
    float n2;
    
    // Gelme açýsý ve kýrýlma açýþý
    float angleOfIncidence;
	float angleOfRefraction;
	
	// Kritik açý
    float critAngle;
    
    // Ekran boyutlarý
    int windowSizeX = window.getSize().x;
    int windowSizeY = window.getSize().y;
	
	Medias fMedia = Medias::Oliveoil;
	Medias sMedia = Medias::Water;
	
	n1 = getRefractiveIndex(&fMedia);
	n2 = getRefractiveIndex(&sMedia);
	
	angleOfIncidence = 67;
	
	angleOfRefraction = radianToAngle( asin( (n1 / n2) * sin(angleToRadian(angleOfIncidence)) ) );

	sf::RectangleShape principalAxis, normal, incidentRay, refractedRay, reflectedRay;
	sf::RectangleShape bcUp, bcDown;
	
	bcUp.setSize(sf::Vector2f( windowSizeX, windowSizeY / 2 ));
	bcUp.setPosition(sf::Vector2f(0, 0));
	bcUp.setFillColor(getBcColor(&fMedia));
	
	bcDown.setSize(sf::Vector2f( windowSizeX, windowSizeY / 2 ));
	bcDown.setPosition(sf::Vector2f(0, windowSizeY / 2));
	bcDown.setFillColor(getBcColor(&sMedia));

	principalAxis.setSize(sf::Vector2f( windowSizeX, 10 ));
	principalAxis.setOrigin(sf::Vector2f(0 , principalAxis.getSize().y / 2));
	principalAxis.setPosition(sf::Vector2f(0, windowSizeY / 2 ));
	
	normal.setSize(sf::Vector2f( 10, windowSizeY ));
	normal.setOrigin(sf::Vector2f(normal.getSize().x / 2 , 0));
	normal.setPosition(sf::Vector2f(windowSizeX / 2,  0));
	
	incidentRay.setSize(sf::Vector2f( 5, windowSizeY / 2 + 100.f));
	incidentRay.setOrigin(sf::Vector2f(incidentRay.getSize().x / 2, incidentRay.getSize().y));
	incidentRay.setPosition(sf::Vector2f(windowSizeX / 2,  windowSizeY / 2));
	incidentRay.setFillColor(sf::Color::Red);
	incidentRay.setRotation(-angleOfIncidence);
	
	refractedRay.setSize(sf::Vector2f( 5 ,normal.getSize().y / 2 + 100.f));
	refractedRay.setOrigin(sf::Vector2f(refractedRay.getSize().x / 2, 0));
	refractedRay.setPosition(sf::Vector2f(windowSizeX / 2, windowSizeY / 2));
	refractedRay.setFillColor(sf::Color::Red);
	refractedRay.setRotation(-angleOfRefraction);
	
	reflectedRay.setSize(sf::Vector2f( 5 , normal.getSize().y / 2 + 100.f));
	reflectedRay.setOrigin(sf::Vector2f(reflectedRay.getSize().x / 2, reflectedRay.getSize().y));
	reflectedRay.setPosition(sf::Vector2f(windowSizeX / 2, windowSizeY / 2));
	reflectedRay.setFillColor(sf::Color(255, 0, 0, 150));
	reflectedRay.setRotation(angleOfIncidence);
	
	sf::Font font;
	
	font.loadFromFile("tr_arial.ttf");
	
	sf::Text angleOfIncidence_t, angleOfRefraction_t, f_media, s_media, n1_t, n2_t, critAngle_t;
	sf::Text principalAxis_t, normal_t;
	
	angleOfIncidence_t.setFont(font);
	angleOfIncidence_t.setCharacterSize(50);
	angleOfIncidence_t.setPosition(sf::Vector2f(windowSizeX - 450.f, 20.f));
	angleOfIncidence_t.setString("Gelme Açýsý = " + to_string( int(angleOfIncidence)) + "°");
	
	angleOfRefraction_t.setFont(font);
	angleOfRefraction_t.setCharacterSize(50);
	angleOfRefraction_t.setPosition(sf::Vector2f(windowSizeX - 450.f, 90.f));
	angleOfRefraction_t.setString("Kýrýlma Açýsý = " + to_string( int(angleOfRefraction)) + "°");
	
	f_media.setFont(font);
	f_media.setCharacterSize(50);
	f_media.setPosition(sf::Vector2f(50.f,100.f));
	f_media.setString(getNameOfTheMedia(&fMedia));
	f_media.setFillColor(sf::Color::Black);	
	
	s_media.setFont(font);
	s_media.setCharacterSize(50);
	s_media.setPosition(sf::Vector2f(50.f,400.f));
	s_media.setString(getNameOfTheMedia(&sMedia));	
	s_media.setFillColor(sf::Color::Black);	
	
	n1_t.setFont(font);
	n1_t.setCharacterSize(30);
	n1_t.setPosition(sf::Vector2f(75.f, 200.f));
	n1_t.setFillColor(sf::Color::Black);	
	
	n2_t.setFont(font);
	n2_t.setCharacterSize(30);
	n2_t.setPosition(sf::Vector2f(75.f, 500.f));
	n2_t.setFillColor(sf::Color::Black);
	
	critAngle_t.setFont(font);
	critAngle_t.setCharacterSize(30);
	critAngle_t.setPosition(sf::Vector2f(windowSizeX - 220.f, windowSizeY / 2 + 20.f));
	
	principalAxis_t.setFont(font);
	principalAxis_t.setCharacterSize(30);
	principalAxis_t.setPosition(sf::Vector2f(windowSizeX - 220.f, windowSizeY / 2 - 50.f));
	principalAxis_t.setString("Asal Eksen");	
	principalAxis_t.setFillColor(sf::Color::Black);	
	
	normal_t.setFont(font);
	normal_t.setCharacterSize(30);
	normal_t.setPosition(sf::Vector2f(windowSizeX / 2 + 50.f, 20));
	normal_t.setString("Normal");	
	normal_t.setFillColor(sf::Color::Black);	
	normal_t.setRotation(90);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    			window.close();	
		 
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{	
 				if(sf::Mouse::getPosition(window).y < windowSizeY / 2) 
				{
				 	--fMedia;
				 	
				 	n1 = getRefractiveIndex(&fMedia);
				 	f_media.setString(getNameOfTheMedia(&fMedia));	
				 	bcUp.setFillColor(getBcColor(&fMedia));	
				}
			 				 		
				else 
				{
					--sMedia;
					
					n2 = getRefractiveIndex(&sMedia);
				 	s_media.setString(getNameOfTheMedia(&sMedia));	
				 	bcDown.setFillColor(getBcColor(&sMedia));	
				}
			 		
			} 
			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{	
 				if(sf::Mouse::getPosition(window).y < windowSizeY / 2) 
				{
					++fMedia;
					
					n1 = getRefractiveIndex(&fMedia);
				 	f_media.setString(getNameOfTheMedia(&fMedia));	
				 	bcUp.setFillColor(getBcColor(&fMedia));	
				}
			 				 	
				else 
				{
					++sMedia;
					
					n2 = getRefractiveIndex(&sMedia);
				 	s_media.setString(getNameOfTheMedia(&sMedia));	
				 	bcDown.setFillColor(getBcColor(&sMedia));	
				}		
			}
			  
        }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && angleOfIncidence < 90)
		{
    		incidentRay.rotate(-1);
    		angleOfIncidence++;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && angleOfIncidence > 0)
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
			
			critAngle = radianToAngle( asin( (n2 / n1) ) );
			
			angleOfRefraction = radianToAngle(asin( (n1 / n2) * sin(angleToRadian(angleOfIncidence))));
			
			reflectedRay.setRotation(angleOfIncidence);
			
			if(int(angleOfIncidence) == int(critAngle)) 
			{
				angleOfRefraction = 90;
				refractedRay.setRotation(-angleOfRefraction);	
			}
				
				
			if(int(angleOfIncidence) < int(critAngle)) 
			{
				reflectedRay.setFillColor(sf::Color(255, 0, 0, 150));	
				refractedRay.setRotation(-angleOfRefraction);
			}
				
			if(int(angleOfIncidence) > int(critAngle))
			{
				reflectedRay.setFillColor(sf::Color::Red);
				refractedRay.setRotation(-angleOfRefraction);
			}
		}
		
		angleOfIncidence_t.setString("Gelme Açýsý = " + to_string( int(angleOfIncidence)) + "°");
		
		if(n2 >= n1)
			angleOfRefraction_t.setString("Kýrýlma Açýsý = " + to_string( int(angleOfRefraction)) + "°");
	    else 
		{
			if(int(angleOfIncidence) > int(critAngle))
				angleOfRefraction_t.setString("Yansýma açýsý = " + to_string( int(angleOfIncidence)) + "°");
			else
				angleOfRefraction_t.setString("Kýrýlma Açýsý = " + to_string( int(angleOfRefraction)) + "°");
		}
	        
		n1_t.setString("n1 = " + to_string(n1));		
		n2_t.setString("n2 = " + to_string(n2));
		
		critAngle_t.setString("Kritik açý = " + to_string(int(critAngle)) + "°");

        window.clear();
        window.draw(bcUp);
        window.draw(bcDown);
        window.draw(principalAxis);
        window.draw(normal);
        window.draw(incidentRay);
        window.draw(refractedRay);
			
		if(n1 > n2 && !(int(angleOfIncidence) == int(critAngle)))	 
		{
			window.draw(reflectedRay);
		}	
		
		if(n1 > n2) 
 			window.draw(critAngle_t);
        
        window.draw(angleOfIncidence_t);
        window.draw(angleOfRefraction_t);
        window.draw(f_media);
        window.draw(s_media);
        window.draw(n1_t);
        window.draw(n2_t);
        window.draw(principalAxis_t);
		window.draw(normal_t);
        window.display();
    }

    return 0;
}	
