package main

import "fmt"

func main() {
	//fmt.Println("hello world")
	var (
		a float64 = 1
		b float64 = 2
		c float64 = -3
		discr float64 = b*b - 4*a*c
	)
	if discr >= 0 {
		fmt.Println("x1 = ", (-b - Sqrt(discr))/(2*a), "\nx2 = ", (-b + Sqrt(discr))/(2*a))
	} else {
		fmt.Println("Дискриминант меньше нуля. Корней нет. :(")
	}
}


func Sqrt(x float64) float64{
	root := x/2
	var eps float64 = 0.000001
	for root - x/root > eps {
		root = 0.5 * (root + x / root)
	}
	if root - float64(int(root)) < eps{
		root = float64(int(root))
	}
	return root
}