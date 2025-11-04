.PHONY: all 1 2 clean

all: 1

# Ejercicio 1
1:
	@echo "Compilando y ejecutando ej1..."
	@gcc -o ej1 ej1.c -pthread -O2 -Wall
	@./ej1

# Ejercicio 2
2:
	@echo "Compilando ej2_monitoring..."
	@gcc -o ej2_monitoring ej2_monitoring.c -pthread -O2 -Wall
	@echo "Compilando ej2_sensor..."
	@gcc -o ej2_sensor ej2_sensor.c -O2 -Wall
	@echo ""
	@echo ">>> IMPORTANTE: Para ver ej2 correctamente, abrí DOS terminales."
	@echo "En la PRIMERA terminal ejecutá:"
	@echo "  ./ej2_sensor"
	@echo "En la SEGUNDA terminal ejecutá:"
	@echo "  sudo ./ej2_monitoring"

clean:
	@rm -f ej1 ej2_monitoring ej2_sensor
