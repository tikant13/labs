package main

import (
	"fmt"
	"math"
)

// nod вычисляет наибольший общий делитель (аналог НОД)
func nod(a, b int64) int64 {
	for b != 0 {
		a %= b
		a, b = b, a // В Go swap делается одной строкой
	}
	return a
}

func main() {
	var a, b int64
	// Считываем входные данные
	if _, err := fmt.Scan(&a, &b); err != nil {
		return
	}

	// Если ряд расходится (знаменатель прогрессии <= 1)
	if b <= 1 {
		fmt.Println("infinity")
		return
	}

	var sum float64
	var term float64

	// Вычисляем сумму ряда (аналог цикла по n)
	for n := 1; n <= 1000; n++ {
		// Вычисляем n^a
		numerator := 1.0
		for i := int64(0); i < a; i++ {
			numerator *= float64(n)
		}

		// Вычисляем b^n
		denominator := 1.0
		for i := 0; i < n; i++ {
			denominator *= float64(b)
		}

		term = numerator / denominator
		sum += term

		// Если слагаемое стало пренебрежимо малым, выходим
		if term < 1e-15 {
			break
		}
	}

	var bestNum int64 = 1
	var bestDen int64 = 1
	bestDiff := 1e18

	// Перебираем знаменатели для поиска наилучшего приближения дроби
	for den := int64(1); den <= 10000; den++ {
		// Находим ближайший числитель
		num := int64(sum*float64(den) + 0.5)

		// Проверяем точность приближения
		diff := math.Abs(float64(num)/float64(den) - sum)

		if diff < bestDiff {
			bestDiff = diff
			bestNum = num
			bestDen = den
		}
	}

	// Сокращаем полученную дробь
	common := nod(bestNum, bestDen)
	fmt.Printf("%d/%d\n", bestNum/common, bestDen/common)
}