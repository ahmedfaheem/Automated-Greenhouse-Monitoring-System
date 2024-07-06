
#ifndef LCD_INT_H_
#define LCD_INT_H_



void LCD_Init(void);

void LCD_WriteString(c8*str);
void LCD_WriteChar(u8 ch);
void LCD_WriteNumber(s32 num);
void LCD_WriteBinary(u8 num);
void LCD_WriteHex(u8 num);

/* line 0:1 cell 0:15*/
void LCD_SetCursor(u8 line ,u8 cell);

void LCD_ClearCursor(u8 line,u8 cell,u8 NofCells);

void LCD_WriteStringCursor(u8 line,u8 cell,c8 *str);

void LCD_CustomChar(u8 address,u8*pattern);



/* move on LCD*/

void LCD_Clear(void);




#endif /* LCD_INT_H_ */