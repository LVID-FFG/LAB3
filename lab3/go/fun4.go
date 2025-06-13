package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Pair struct {
	First  int
	Second int
}

func stratMaxScore(s, m int, posl []int) Pair {
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
	return Pair{bestM, ourResBest}
}

func stratBestScore(s, m int, posl []int) Pair {
	bestM := 0
	ourResBest := -999999
	difference := -999999

	for j := 1; j <= m; j++ {
		ourRes := 0
		for i := 0; i < j && s+i < len(posl); i++ {
			ourRes += posl[s+i]
		}
		enemy := stratMaxScore(s+j, m, posl)
		if ourRes-enemy.Second > difference {
			difference = ourRes - enemy.Second
			ourResBest = ourRes
			bestM = j
		}
	}

	if bestM == 0 {
		bestM = 1
	}
	return Pair{bestM, ourResBest}
}

func fun4(m int) {
	reader := bufio.NewReader(os.Stdin)
	fmt.Println("Введите последовательность чисел через пробел, для завершения ввода нажмите Enter:")
	input, _ := reader.ReadString('\n')
	input = strings.TrimSpace(input)

	var posl []int
	for _, numStr := range strings.Fields(input) {
		num, err := strconv.Atoi(numStr)
		if err != nil {
			continue
		}
		posl = append(posl, num)
	}

	s := 0
	pavelScore := 0
	vikaScore := 0
	turn := 0

	for s < len(posl) {
		score := stratBestScore(s, m, posl)
		if turn%2 == 0 {
			pavelScore += score.Second
		} else {
			vikaScore += score.Second
		}
		s += score.First
		turn++
	}

	if pavelScore > vikaScore {
		fmt.Println("1") // PAVEL WIN
	} else {
		fmt.Println("0") // VIKA WIN
	}
}
