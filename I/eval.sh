for f in test/*.in.*
do
  echo $f
  ./$1 < $f > out
  ./checker $f ${f/in/out} out
  echo ""
done

rm out
