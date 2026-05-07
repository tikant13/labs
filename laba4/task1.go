package main

import (
	"fmt"
	"math"
)

// Исходная функция f(x)
func f(x float64) float64 {
	return math.Cos(x+0.5) - x - 2
}

// Производная f(x) для метода Ньютона
func df(x float64) float64 {
	return -math.Sin(x+0.5) - 1
}

// Функция x = phi(x) для метода итераций
func phi(x float64) float64 {
	return math.Cos(x+0.5) - 2
}

func main() {
	eps := 0.0001

	// --- Метод половинного деления ---
	fmt.Println("--- Метод половинного деления ---")
	a, b := -2.0, -1.0
	
	fmt.Printf("%-3s %-10s %-10s %-10s\n", "N", "an", "bn", "bn-an")
	
	iteration := 0
	for math.Abs(b-a) > eps {
		diff := math.Abs(b - a)
		fmt.Printf("%-3d %-10.5f %-10.5f %-10.5f\n", iteration, a, b, diff)
		
		c := (a + b) / 2.0
		if f(a)*f(c) < 0 {
			b = c
		} else {
			a = c
		}
		iteration++
	}
	fmt.Printf("Корень: %.5f\n\n", (a+b)/2.0)

	// --- Метод Ньютона ---
	fmt.Println("--- Метод Ньютона ---")
	xNewt := -1.5
	fmt.Printf("%-3s %-10s %-10s %-10s\n", "N", "xn", "xn+1", "|xn+1-xn|")
	
	for i := 0; i < 100; i++ {
		xNext := xNewt - f(xNewt)/df(xNewt)
		d := math.Abs(xNext - xNewt)
		
		fmt.Printf("%-3d %-10.5f %-10.5f %-10.5f\n", i, xNewt, xNext, d)
		
		xNewt = xNext
		if d < eps {
			break
		}
	}
	fmt.Printf("Корень: %.5f\n\n", xNewt)

	// --- Метод простых итераций ---
	fmt.Println("--- Метод простых итераций ---")
	xIt := -1.5
	fmt.Printf("%-3s %-10s %-10s %-10s\n", "N", "xn", "xn+1", "|xn+1-xn|")
	
	for i := 0; i < 100; i++ {
		xNext := phi(xIt)
		d := math.Abs(xNext - xIt)
		
		fmt.Printf("%-3d %-10.5f %-10.5f %-10.5f\n", i, xIt, xNext, d)
		
		xIt = xNext
		if d < eps {
			break
		}
	}
	fmt.Printf("Корень: %.5f\n", xIt)
}