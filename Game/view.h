#include <SFML/Graphics.hpp>

using namespace sf;

View view;

void getPlayerCoordinateForView(float x, float y)
{
	float tempX = x; float tempY = y;//��������� ����� ������ � ��������� ��, ����� ������ ����

	if (x < 480) tempX = 480;//������� �� ���� ����� �������
	if (y < 320) tempY = 320;//������� �������
	if (y > 320) tempY = 320;//������ �������	
	if (x > 480) tempX = 480;

	view.setCenter(tempX, tempY); //������ �� �������, ��������� ��� ����������
}