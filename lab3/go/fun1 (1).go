package main

import (
	"fmt"
	"math"
)

func fun1(x_s, x_con, step float64) {
	var results []float64
	x := x_s

	for ; x <= x_con; x += step {
		var y float64

		switch {
		case x < -10:
			y = 2
		case -10 <= x && x <= -6:
			y = -1*math.Sqrt(4-math.Pow(x+8, 2)) + 2
		case -6 < x && x <= -4:
			y = 2
		case -4 < x && x <= 2:
			y = -1 * (x / 2)
		case x > 2:
			y = x - 3
		default:
			y = 0 // для случая currentX == 2
		}

		results = append(results, y)
	}

	fmt.Println("x y")
	printX := x_s
	for _, y := range results {
		fmt.Printf("%.2f %.2f\n", printX, y)
		printX += step
	}
}
