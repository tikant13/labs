package main

import (
	"fmt"
)

// input считывает данные о кандидатах и голосах групп
func input(n, m int) ([]string, []int, [][]int) {
	candidates := make([]string, n)
	voters := make([]int, m)
	ranking := make([][]int, m)

	fmt.Println("Введите имена кандидатов:")
	for i := 0; i < n; i++ {
		fmt.Scan(&candidates[i])
	}

	fmt.Println("Для каждой группы сначала количество избирателей,")
	fmt.Println("затем порядок кандидатов (от лучшего к худшему, индексы от 1 до n):")

	for i := 0; i < m; i++ {
		fmt.Printf("Группа %d:\n", i+1)
		fmt.Scan(&voters[i])

		ranking[i] = make([]int, n)
		for j := 0; j < n; j++ {
			var val int
			fmt.Scan(&val)
			ranking[i][j] = val - 1 // приводим к 0-индексации
		}
	}

	return candidates, voters, ranking
}

func main() {
	var n, m int

	fmt.Print("Количество кандидатов: ")
	fmt.Scan(&n)

	fmt.Print("Количество групп избирателей: ")
	fmt.Scan(&m)

	candidates, voters, ranking := input(n, m)

	// --- Метод Борда ---
	borda := make([]int, n)
	for i := 0; i < m; i++ { // по группам
		for pos := 0; pos < n; pos++ { // по позициям
			candidate := ranking[i][pos]
			// Очки: (n - позиция - 1). Первое место (pos=0) дает n-1 очков.
			borda[candidate] += (n - pos - 1) * voters[i]
		}
	}

	bordaWinner := 0
	for i := 1; i < n; i++ {
		if borda[i] > borda[bordaWinner] {
			bordaWinner = i
		}
	}

	// --- Метод Кондорсе ---
	condorcetWinner := -1

	for a := 0; a < n; a++ {
		winsAll := true // гипотеза: кандидат 'a' побеждает всех

		for b := 0; b < n; b++ {
			if a == b {
				continue
			}

			votesA := 0
			votesB := 0

			for g := 0; g < m; g++ {
				posA, posB := 0, 0
				for k := 0; k < n; k++ {
					if ranking[g][k] == a {
						posA = k
					}
					if ranking[g][k] == b {
						posB = k
					}
				}

				if posA < posB {
					votesA += voters[g]
				} else {
					votesB += voters[g]
				}
			}

			// Если в паре (a, b) 'a' не набрал строго больше голосов, он не Кондорсе-победитель
			if votesA <= votesB {
				winsAll = false
				break
			}
		}

		if winsAll {
			condorcetWinner = a
			break
		}
	}

	// --- Вывод результатов ---
	fmt.Println("\nМетод Борда:")
	for i := 0; i < n; i++ {
		fmt.Printf("%s: %d очков\n", candidates[i], borda[i])
	}
	fmt.Printf("Победитель: %s (%d очков)\n", candidates[bordaWinner], borda[bordaWinner])

	fmt.Println("\nМетод Кондорсе:")
	if condorcetWinner == -1 {
		fmt.Println("Победитель не определён (парадокс Кондорсе)")
	} else {
		fmt.Printf("Победитель: %s\n", candidates[condorcetWinner])
	}
}