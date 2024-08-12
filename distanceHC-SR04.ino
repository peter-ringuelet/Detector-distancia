const int trigPin = 7;  // Pin de Trigger del HC-SR04
const int echoPin = 6;  // Pin de Echo del HC-SR04
long duration;          // Variable para almacenar la duración del pulso de eco
float distance;         // Variable para almacenar la distancia calculada
float totalDistance = 0;
int numReadings = 10;   // Número de mediciones para promediar

void setup() {
  pinMode(trigPin, OUTPUT);  // Configurar el pin Trig como salida
  pinMode(echoPin, INPUT);   // Configurar el pin Echo como entrada
  Serial.begin(9600);        // Iniciar la comunicación serial a 9600 bps
}

void loop() {
  totalDistance = 0;  // Reiniciar la suma de distancias

  for (int i = 0; i < numReadings; i++) {
    // Enviar un pulso de 10 microsegundos desde el pin Trig
    digitalWrite(trigPin, LOW);   // Asegurarse de que el pin Trig esté en LOW
    delayMicroseconds(2);         // Esperar 2 microsegundos
    digitalWrite(trigPin, HIGH);  // Enviar un pulso de 10 microsegundos
    delayMicroseconds(10);        // Mantener el pulso durante 10 microsegundos
    digitalWrite(trigPin, LOW);   // Volver el pin Trig a LOW

    // Leer la duración del pulso en el pin Echo
    duration = pulseIn(echoPin, HIGH);

    // Calcular la distancia en metros
    distance = duration * 0.034 / 200;

    // Filtrar distancias fuera del rango esperado (menor a 0.02m o mayor a 4.0m)
    if (distance >= 0.02 && distance <= 4.0) {
      totalDistance += distance;  // Sumar solo las lecturas válidas
    }

    delay(10); // Pequeña pausa entre mediciones
  }

  // Calcular el promedio de las distancias válidas
  distance = totalDistance / numReadings;

  // Mostrar la distancia promedio en el Monitor Serial
  if ( distance >= 0.02 && distance <= 4.0 ){
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" m");
  }

  delay(500); // Esperar 500 ms antes de tomar otra medición
}
