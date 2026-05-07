package main

import (
	"fmt"
	"math"
)

// printFun выводит строку таблицы с заданным форматированием
func printFun(x, y float64) {
	
	fmt.Printf("|%11g|%11.4f|\n", x, y)
	fmt.Println("-------------------------")
}

func main() {
	var x, xk, step float64

	fmt.Println("Введите x начальное и x конечное")
	fmt.Scan(&x, &xk)
	fmt.Println("Введите шаг")
	fmt.Scan(&step)

	fmt.Println("-------------------------")
	fmt.Println("|     x     |     y     |")
	fmt.Println("-------------------------")

	// В Go нет цикла while, используется for с условием
	for x <= xk {
		var y float64

		if x >= -9 && x <= -5 { // полуокружность
			y = 2 - math.Sqrt(4-math.Pow(x+7, 2))
		} else if x > -5 && x <= -4 { // линия горизонтальная
			y = 2
		} else if x > -4 && x <= 0 { // наклонная
			y = -0.5 * x
		} else if x > 0 && x < 3 { // парабола
			y = -0.5 * x * (x - 3)
		} else if x >= 3 { // наклонная
			y = x - 3
		}

		if x >= -9 {
			printFun(x, y)
		}

		x += step
	}
}