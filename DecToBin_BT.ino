/*
   ENVIO Y RECEPCION DE DATOS MEDIANTE BT - ARDUINO
   El numero 3 es mi favorito :)
   Mediante una aplicacion Android (BlueTooth Serial Controller), configurada segun la necesidad del programa
   se envia un numero (de 0 a 15) y este es convertido a binario naturar de 4 bits ("000" - "1111"). El numero binario
   es mostrado en leds; tambien se visualiza el estado actual de los leds en la aplicacion Android (H = '1', L = '0')

   Para estudiantes de Programacion I - EIE FIA UES
*/
int ledArray[4];
int numeroSerial[2] = {0, 0}; //se reciben 2 numeros (en codigo ASCII) de la aplicacion Android
int numero;
char* bin[4]; //notar que es CHAR*!!!

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i <= 3; i++) {
    ledArray[i] = i + 2;
    pinMode(ledArray[i], OUTPUT);
  }//Se inicializa el arreglo de leds en modo de salida.
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) { //Para la recepcion serial
    for (int i = 0; i <= 1; i++) {
      numeroSerial[i] = Serial.read() - 48; // se resta 48 porque se recibe un ascii (revisar codigo ascii para lo que se necesite)
      Serial.print(numeroSerial[i]); // muestra lo que se recibe
      if (i == 1) {
        Serial.println();
      }
    }
    numero = numeroSerial[0] * 10 + numeroSerial[1]; //se convierte de un vector de 2 numeros enteros a un solo numero
    convToBin(numero); //funcion para convertir a binario natural de 4 bits
    delay(100);
    Serial.println(numero);
    delay(10);
  }
  delay(420); // no tiene nada que ver con sustancias ilicitas :)
}

//Funcion para convertir numero base decimal (0 - 15) a binario natural de 4 bits ("0000" - "1111")
void convToBin(int N) {
  int n = 4; //en lo que iba probando para arreglar uno errores puse esto y ya no quiero tocar mas el codigo :)
  int N_bin[n]; //pero aqui si es necesario ese n = 4
  char* bin[n];
  switch (N) { // switch-case puede ahorrar ciertas operaciones :)
    case 0: bin[n] = "LLLL"; break;
    case 1: bin[n] = "LLLH"; break;
    case 2: bin[n] = "LLHL"; break;
    case 3: bin[n] = "LLHH"; break;
    case 4: bin[n] = "LHLL"; break;
    case 5: bin[n] = "LHLH"; break;
    case 6: bin[n] = "LHHL"; break;
    case 7: bin[n] = "LHHH"; break;
    case 8: bin[n] = "HLLL"; break;
    case 9: bin[n] = "HLLH"; break;
    case 10: bin[n] = "HLHL"; break;
    case 11: bin[n] = "HLHH"; break;
    case 12: bin[n] = "HHLL"; break;
    case 13: bin[n] = "HHLH"; break;
    case 14: bin[n] = "HHHL"; break;
    case 15: bin[n] = "HHHH"; break;
    default: Serial.println("no"); break;
  }
  Serial.println(bin[n]);
  delay(50);
  //este for() es para converir N (base 10) a binario natural)
  for (int i = 0; i <= n - 1; i++) {
    N_bin[i] =  N % 2;
    N = N / 2;
  }
  //Aca se enciende los leds segun corresponda (H = '1'; L = '0')
  for (int i = 0; i < 4; i++) {
    if (N_bin[i] == 0) {
      digitalWrite(ledArray[i], LOW);
    } else if (N_bin[i] == 1) {
      digitalWrite(ledArray[i], HIGH);
    }
  }
}
