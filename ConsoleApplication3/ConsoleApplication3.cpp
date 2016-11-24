//Inga Melkerte
//C00184799
//24/11/16
//Robot Arm
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
////////////////////////////////////////////////////////////
///Entrypoint of application 
////////////////////////////////////////////////////////////
int main()
{
	int width = 900;
	int height = 700;
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(width, height, 32), "SFML First Program");
	window.setFramerateLimit(60);
	const int size = 5;
	
	sf::VertexArray linesA(sf::LinesStrip, size);
	sf::VertexArray linesE(sf::LinesStrip, size);
	sf::VertexArray linesJ1(sf::LinesStrip, size);
	sf::VertexArray linesJ2(sf::LinesStrip, size);
	sf::VertexArray linesJ11(sf::LinesStrip, size);
	sf::VertexArray linesJ21(sf::LinesStrip, size);
	//position of the arm 
	sf::Vector2f pos(300, 360);
	//arm,elbow
	sf::Vector2f pointsS[size];
	pointsS[0] = sf::Vector2f(0, 15);
	pointsS[1] = sf::Vector2f(140, 15);
	pointsS[2] = sf::Vector2f(140, -15);
	pointsS[3] = sf::Vector2f(0, -15);
	pointsS[4] = pointsS[0];
	//jaw
	sf::Vector2f pointsJ[size];
	pointsJ[0] = sf::Vector2f(0, 0);
	pointsJ[1] = sf::Vector2f(0, -90);
	pointsJ[2] = sf::Vector2f(20, -90);
	pointsJ[3] = sf::Vector2f(20, 0);	
	pointsJ[4] = pointsJ[0];
	//jaw2
	sf::Vector2f pointsJ2[size];
	pointsJ2[0] = sf::Vector2f(0, 0);
	pointsJ2[1] = sf::Vector2f(0, 90);
	pointsJ2[2] = sf::Vector2f(20, 90);
	pointsJ2[3] = sf::Vector2f(20, 0);
	pointsJ2[4] = pointsJ2[0];
	//claws
	sf::Vector2f pointsJ11[size];
	pointsJ11[0] = sf::Vector2f(0, 0);
	pointsJ11[1] = sf::Vector2f(70, 0);
	pointsJ11[2] = sf::Vector2f(90, 20);
	pointsJ11[3] = sf::Vector2f(0, 20);
	pointsJ11[4] = pointsJ11[0];
	//claws
	sf::Vector2f pointsJ21[size];
	pointsJ21[0] = sf::Vector2f(0, 0);
	pointsJ21[1] = sf::Vector2f(90, 0);
	pointsJ21[2] = sf::Vector2f(70, 20);
	pointsJ21[3] = sf::Vector2f(0, 20);
	pointsJ21[4] = pointsJ21[0];

	float rotation = 0.0;
	float rotationE = 0.0;
	float rotationJ1 = 30.0;
	float rotationJ2 = -30.0;
	float rotationJ11 = 0.0;
	float rotationJ21 = 0.0;
	//velocity
	float rotationVel = 5.0;

	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				if (rotation < 90)
					rotation += rotationVel;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				if (rotation > -90)
					rotation -= rotationVel;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				if (rotationE > -90)
					rotationE -= rotationVel;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			{
				if (rotationE < 90)
					rotationE += rotationVel;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				if (rotationJ1 < 45)
					rotationJ1 += rotationVel;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				if (rotationJ2 > -45)
					rotationJ2 -= rotationVel;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				if (rotationJ1 > -45)
					rotationJ1 -= rotationVel;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				if (rotationJ2 < 45)
					rotationJ2 += rotationVel;
			}
		}
		//arm
		sf::Transform Ts;
		Ts.translate(pos);
		sf::Transform arm;
		arm.rotate(rotation);
		sf::Transform Marm = Ts*arm;
		
		//elbow
		sf::Vector2f elbowPos (140, 0);
		sf::Transform elbowT;
		elbowT.translate(elbowPos);
		sf::Transform elbowR;
		elbowR.rotate(rotationE);
		sf::Transform elbowM = Marm*elbowT*elbowR;
				
		//Jaws1
		sf::Vector2f posJaws(140, 0);
		sf::Transform jaw1R;
		jaw1R.rotate(rotationJ1);
		
		//Jaws2
		sf::Transform jaw2R;
		jaw2R.rotate(rotationJ2);
		sf::Transform Tj;
		Tj.translate(posJaws);
		
		//Claws
		sf::Transform Jaw11T;
		sf::Vector2f posJaw11(0, 70);
		Jaw11T.translate(posJaw11);
		sf::Transform Jaw11R;
		Jaw11R.rotate(rotationJ11);

		//Claws
		sf::Transform Jaw21T;
		sf::Vector2f posJaw21(0, -90);
		Jaw21T.translate(posJaw21);
		sf::Transform Jaw21R;
		Jaw21R.rotate(rotationJ21);

		//transformations
		sf::Transform Mjaw1 = Ts*arm*elbowT*elbowR*Tj*jaw1R;
		sf::Transform Mjaw2 = Ts*arm*elbowT*elbowR*Tj*jaw2R;
		sf::Transform Mjaw11 = Mjaw2*Jaw11T;
		sf::Transform Mjaw21 = Mjaw1*Jaw21T;

		//update arm, elbow, jaws and claws
		for (int i = 0;i < size;i++) {
			linesA[i].position = Marm.transformPoint(pointsS[i]);
			linesA[i].color = sf::Color::Blue;
			linesE[i].position = elbowM.transformPoint(pointsS[i]);
			linesE[i].color = sf::Color::Green;
			linesJ1[i].position = Mjaw1.transformPoint(pointsJ[i]);
			linesJ1[i].color = sf::Color::Red;
			linesJ2[i].position = Mjaw2.transformPoint(pointsJ2[i]);
			linesJ2[i].color = sf::Color::Red;			
			linesJ11[i].position = Mjaw11.transformPoint(pointsJ11[i]);
			linesJ11[i].color = sf::Color::Red;
			linesJ21[i].position = Mjaw21.transformPoint(pointsJ21[i]);
			linesJ21[i].color = sf::Color::Red;
		}
		//prepare frame
		window.clear();
		window.draw(linesA);
		window.draw(linesE);
		window.draw(linesJ1);
		window.draw(linesJ2);
		window.draw(linesJ11);
		window.draw(linesJ21);
		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}