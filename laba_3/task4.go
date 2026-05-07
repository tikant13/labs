package main

import (
	"fmt"
)

func main() {
	var n, m int
	// Считываем n и m
	if _, err := fmt.Scan(&n, &m); err != nil {
		return
	}

	a := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&a[i])
	}

	// Префиксные суммы
	// prefix[i+1] хранит сумму первых i элементов
	prefix := make([]int, n+1)
	for i := 0; i < n; i++ {
		prefix[i+1] = prefix[i] + a[i]
	}

	pavelScore, vikaScore := 0, 0
	pos := 0
	lastPavel := -1 // сколько взял Павел в прошлый раз
	lastVika := -1  // сколько взяла Вика в прошлый раз
	turn := 0       // 0 - Павел, 1 - Вика

	for pos < n {
		maxTake := m
		if n-pos < maxTake {
			maxTake = n - pos
		}

		forbidden := -1
		if turn == 0 {
			forbidden = lastPavel
		} else {
			forbidden = lastVika
		}

		bestSum := -1
		bestTake := 1

		for take := 1; take <= maxTake; take++ {
			if take == forbidden {
				continue
			}

			// Вычисляем сумму на отрезке через префиксные суммы
			sum := prefix[pos+take] - prefix[pos]

			// при равенстве — минимальное количество элементов
			if sum > bestSum || (sum == bestSum && take < bestTake) {
				bestSum = sum
				bestTake = take
			}
		}

		
		if bestSum == -1 {
			break
		}

		if turn == 0 {
			pavelScore += bestSum
			lastPavel = bestTake
		} else {
			vikaScore += bestSum
			lastVika = bestTake
		}

		pos += bestTake
		turn = 1 - turn
	}

	
	if pavelScore > vikaScore {
		fmt.Println(1)
	} else {
		fmt.Println(0)
	}
}