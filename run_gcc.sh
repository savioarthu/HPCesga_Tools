#!/bin/sh
# on CESGA's FT-II system.
#----------------------------------------------------
#SBATCH -N 1 #(1 node)
#SBATCH -n 1 #(1 job)
#SBATCH -c 24 #(24 cores per job)
#SBATCH -t 15:10:00 #(execution time)

# Run the CUDA application
export OMP_NUM_THREADS=8

echo -e "Execution 0 : \n"

	echo "Small test"
	./dgesv0_gcc 1024

	echo "Medium test"
	./dgesv0_gcc 2048

	echo "Large test"
	./dgesv0_gcc 4096

echo -e "Execution 1 : \n"

	echo "Small test"
	./dgesv1_gcc 1024

	echo "Medium test"
	./dgesv1_gcc 2048

	echo "Large test"
	./dgesv1_gcc 4096

echo -e "Execution 2 : \n"
	echo "Small test"
	./dgesv2_gcc 1024

	echo "Medium test"
	./dgesv2_gcc 2048

	echo "Large test"
	./dgesv2_gcc 4096

echo -e "Execution 3 : \n"
	echo "Small test"
	./dgesv3_gcc 1024

	echo "Medium test"
	./dgesv3_gcc 2048

	echo "Large test"
	./dgesv3_gcc 4096

echo -e "Execution fast : \n"
	echo "Small test"
	./dgesvfast_gcc 1024

	echo "Medium test"
	./dgesvfast_gcc 2048

	echo "Large test"
	./dgesvfast_gcc 4096

echo -e "Execution ipo : \n"
	echo "Small test"
	./dgesvipo_gcc 1024

	echo "Medium test"
	./dgesvipo_gcc 2048

	echo "Large test"
	./dgesvipo_gcc 4096

echo -e "Execution pgo : \n"
	echo "Small test"
	./dgesvpgo_gcc 1024

	echo "Medium test"
	./dgesvpgo_gcc 2048

	echo "Large test"
	./dgesvpgo_gcc 4096

echo -e "Execution vector : \n"
	echo "Small test"
	./dgesvvect_gcc 1024

	echo "Medium test"
	./dgesvvect_gcc 2048

	echo "Large test"
	./dgesvvect_gcc 4096