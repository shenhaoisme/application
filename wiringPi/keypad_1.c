#include <wiringPi.h>
#include <stdio.h>

#define ROWS 4
#define COLS 4

char pressedKey = '\0';
<<<<<<< HEAD
int rowPins[ROWS] = {25, 28, 29, 0};
int colPins[COLS] = {1, 2, 3, 4};

char keys[ROWS][COLS] = {
   {'1', '2', '3', 'A'},
   {'4', '5', '6', 'B'},
   {'7', '8', '9', 'C'},
   {'*', '0', '#', 'D'}
=======
char last_key = '\0';
int rowPins[ROWS] = {25, 28, 29, 0};
int colPins[COLS] = {1, 2, 3, 4};

int first;
char keys[ROWS][COLS] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
>>>>>>> e64712866530313c83f06b226bdee401bb73f4ab
};

void init_keypad()
{
<<<<<<< HEAD
   for (int c = 0; c < COLS; c++)
   {
      pinMode(colPins[c], OUTPUT);   
      digitalWrite(colPins[c], HIGH);
   }

   for (int r = 0; r < ROWS; r++)
   {
      pinMode(rowPins[0], INPUT);   
      digitalWrite(rowPins[r], PUD_UP);
   }
=======
for (int c = 0; c < COLS; c++)
{
	pinMode(colPins[c], OUTPUT);   
	digitalWrite(colPins[c], HIGH);
}

for (int r = 0; r < ROWS; r++)
{
	pinMode(rowPins[0], INPUT);   
	digitalWrite(rowPins[r], PUD_UP);
}
>>>>>>> e64712866530313c83f06b226bdee401bb73f4ab
}

int findLowRow()
{
<<<<<<< HEAD
   for (int r = 0; r < ROWS; r++)
   {
      if (digitalRead(rowPins[r]) == LOW)
         return r;
   }

   return -1;
=======
	for (int r = 0; r < ROWS; r++)
	{
		if (digitalRead(rowPins[r]) == LOW)
		return r;
	}

	return -1;
>>>>>>> e64712866530313c83f06b226bdee401bb73f4ab
}

char get_key()
{
<<<<<<< HEAD
   int rowIndex;

   for (int c = 0; c < COLS; c++)
   {
      digitalWrite(colPins[c], LOW);

      rowIndex = findLowRow();
      if (rowIndex > -1)
      {
         if (!pressedKey)
            pressedKey = keys[rowIndex][c];
         return pressedKey;
      }

      digitalWrite(colPins[c], HIGH);
   }

   pressedKey = '\0';

   return pressedKey;
=======
	int rowIndex;
	

	for (int c = 0; c < COLS; c++)
	{
	digitalWrite(colPins[c], LOW);

	rowIndex = findLowRow();
	if (rowIndex > -1)
	{
		  if (!pressedKey)
					  pressedKey = keys[rowIndex][c];
			   return pressedKey;
				 }

	digitalWrite(colPins[c], HIGH);
	}
	
	pressedKey = '\0';
	
	return pressedKey;
>>>>>>> e64712866530313c83f06b226bdee401bb73f4ab
}

int main(void) 
{
<<<<<<< HEAD
   wiringPiSetup();

   init_keypad();

   while(1)
   {
      char x = get_key();

      if (x)
         printf("pressed: %c\n", x);
      else
         printf("no key pressed\n");

      delay(250);
   }

   return 0;
}
=======
	wiringPiSetup();

	init_keypad();

	while(1)
	{
		char x = get_key();
		//in case of repeat, just get one value
		/*当当前的值与last_key 相同的话分两种情况：
		1重复按
		2刚开始
		
		不管是哪种情况，就结束本次循环，等一个小延时，还是要就恢复到正常的情况下*/
		if(last_key != x)
			last_key = x;
		else 
		{
			if(first == 0)
				continue;
			else
			{
				first++;
				if(first == 100)
					first =0;
			}
		}
			
		if (x)
			printf("pressed: %c\n", x);
		else
			//printf("no key pressed\n");

		delay(250);
	}

	return 0;
}

>>>>>>> e64712866530313c83f06b226bdee401bb73f4ab
