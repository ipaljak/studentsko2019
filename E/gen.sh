python gen.py

for t in test/*.in.*
do
  ./E < $t > ${t/in/out}
done
