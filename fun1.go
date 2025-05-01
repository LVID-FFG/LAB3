package main

import (
	"fmt"
	"math"
)

func fun1(x, x_con, step float64) {
	var result []float64
	var y float64
	s := x

	for ; x <= x_con; x += step {
		if x < -10 {
			y = 2
		}
		if -10 <= x && x <= -6 {
			y = -1*math.Sqrt(4-math.Pow(x+8, 2)) + 2
		}
		if -6 < x && x <= -4 {
			y = 2
		}
		if -4 < x && x <= 2 {
			y = -1 * (x / 2)
		}
		if 2 < x {
			y = x - 3
		}
		result = append(result, y)
	}

	fmt.Println("x y")
	for _, i := range result {
		fmt.Printf("%.2f %.2f\n", s, i)
		s += step
	}
}