

func main() {

	var(
		baseMinor float64
		answerMatrix [size]float64
		matrix = [size*size]float64{
			2,4,3,
			5,6,2,
			3,12,24,
		}
		helpMatrix = [size]float64{
			1,
			4,
			7,
		}

	)

	// fmt.Println(matrix)
	for i := 0; i < size; i++ {
		baseMinor = baseMinor + solveMinor3x3(matrix, 0, i)
	}
	for i := 0; i < size; i++ {
		answerMatrix[i] = findDeterminant(matrix, helpMatrix, baseMinor,  i)
	}
//	fmt.Println(answerMatrix)
}

func (matrix [3*3]float64, column int, row int) float64 {
	var (
		temp float64 = 0
		tempMatrix [2*2]float64
	)
	var itemp, jtemp int = 0, 0
	for i := 0; i < size; i++{
		if i != column{
			for j := 0; j < size; j++{
					if j != row{
						tempMatrix[itemp*(2)+jtemp] = matrix[i*(3)+j]
						jtemp++
				}
			}
			jtemp = 0
			itemp++
		}
	}
	for i := 0; i < size - 1; i++{
			temp = temp + solveMinor2x2(tempMatrix)
	}
	if (column + row)%2 != 0{
		temp = -1*temp
	}
	return temp*matrix[column*(size) + row]
}
func solveMinor2x2(matrix [2*2]float64) float64{
	return matrix[0]*matrix[3] - matrix[1]*matrix[2]
}
func findDeterminant(matrix [size*size]float64, helpMatrix [size]float64, baseMinor float64, column int) float64{
	var (
		helpMinor float64
		tempMatrix [size*size]float64
	)

	//Я комментарий я тут нахожусь
	for i := 0; i < size; i++{
		for j := 0; j < size; j++{
			tempMatrix[i*size + j] = matrix[i*size + j]
		}
	}
	for i := 0; i < size; i++ {
		tempMatrix[i*size + column] = helpMatrix[i]
	}
	for i := 0; i < size; i++ {
		helpMinor = helpMinor + solveMinor3x3(tempMatrix, 0, i)
	}
	return helpMinor/baseMinor
}