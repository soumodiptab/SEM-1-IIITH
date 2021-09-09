void multiply(sparse_matrix b)
    {
        if (col != b.row)
        {
  
            // Invalid multiplication
            cout << "Can't multiply, Invalid dimensions";
            return;
        }
  
        // transpose b to compare row
        // and col values and to add them at the end
        b = b.transpose();
        int apos, bpos;
  
        // result matrix of dimension row X b.col
        // however b has been transposed,
        // hence row X b.row
        sparse_matrix result(row, b.row);
  
        // iterate over all elements of A
        for (apos = 0; apos < len;)
        {
  
            // current row of result matrix
            int r = data[apos][0];
  
            // iterate over all elements of B
            for (bpos = 0; bpos < b.len;)
            {
  
                // current column of result matrix
                // data[,0] used as b is transposed
                int c = b.data[bpos][0];
  
                // temporary pointers created to add all
                // multiplied values to obtain current
                // element of result matrix
                int tempa = apos;
                int tempb = bpos;
  
                int sum = 0;
  
                // iterate over all elements with
                // same row and col value
                // to calculate result[r]
                while (tempa < len && data[tempa][0] == r &&
                       tempb < b.len && b.data[tempb][0] == c)
                {
                    if (data[tempa][1] < b.data[tempb][1])
  
                        // skip a
                        tempa++;
  
                    else if (data[tempa][1] > b.data[tempb][1])
  
                        // skip b
                        tempb++;
                    else
  
                        // same col, so multiply and increment
                        sum += data[tempa++][2] * 
                             b.data[tempb++][2];
                }
  
                // insert sum obtained in result[r]
                // if its not equal to 0
                if (sum != 0)
                    result.insert(r, c, sum);
  
                while (bpos < b.len && 
                       b.data[bpos][0] == c)
  
                    // jump to next column
                    bpos++;
            }
            while (apos < len && data[apos][0] == r)
  
                // jump to next row
                apos++;
        }
        result.print();
    }