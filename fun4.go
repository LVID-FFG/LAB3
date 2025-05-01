package main

import (
	"fmt"
)

func stratMaxScore(s, m int, posl []int) (int, int) {
	bestM := 0
	ourResBest := -999999

	for j := 1; j <= m; j++ {
		ourRes := 0
		for i := 0; i < j && s+i < len(posl); i++ {
			ourRes += posl[s+i]
		}
		if ourRes > ourResBest {
			ourResBest = ourRes
			bestM = j
		}
	}

	if bestM == 0 {
		bestM = 1
	}
	return bestM, ourResBest
}

func stratBestScore(s, m int, posl []int) (int, int) {
	bestM := 0
	ourResBest := -999999
	difference := -999999

	for j := 1; j <= m; j++ {
		ourRes := 0
		for i := 0; i < j && s+i < len(posl); i++ {
			ourRes += posl[s+i]
		}
		enemyM, enemyScore := stratMaxScore(s+j, m, posl)
		_ = enemyM // unused
		if ourRes-enemyScore > difference {
			difference = ourRes - enemyScore
			ourResBest = ourRes
			bestM = j
		}
	}

	if bestM == 0 {
		bestM = 1
	}
	return bestM, ourResBest
}

func fun4(m int) {
	var posl []int
	var i int

	fmt.Println("Введите последовательность чисел через пробел, для завершенния ввода введите любую букву и enter")
	for {
		_, err := fmt.Scan(&i)
		if err != nil {
			break
		}
		posl = append(posl, i)
	}

	pavelScore := 0
	vikaScore := 0
	s := 0

	for s < len(posl) {
		bestM, score := stratBestScore(s, m, posl)
		pavelScore += score
		s += bestM

		if s >= len(posl) {
			break
		}

		bestM, score = stratBestScore(s, m, posl)
		vikaScore += score
		s += bestM
	}

	if pavelScore > vikaScore {
		fmt.Println("1")
	} else {
		fmt.Println("0")
	}
}