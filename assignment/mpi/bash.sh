echo ""
echo "================================================================================"
echo "|"
echo "|                                Start"
echo "|"
echo "================================================================================"
echo ""

programlist=(MPI_Send_and_Recv MPI_Reduce MPI_Allreduce MPI_Bcast MPI_Scatter_and_Gather MPI_Scatter_and_Allgather MPI_Barrier cpu_time MPI_Type_create_struct)
size=4
for p in ${programlist[*]}
do
    echo "------------------" ${p} "------------------"
    echo ""
    mpiexec -n ${size} ./${p}.out
	echo ""
    echo ""
    echo ""
done

echo ""
echo "================================================================================"
echo "|"
echo "|                                 END!"
echo "|"
echo "================================================================================"
echo ""
# echo ""
# echo "----------------------------------- END -----------------------------------------"
