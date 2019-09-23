#!/bin/sh
# on CESGA's FT-II system.
#----------------------------------------------------
#SBATCH -J gpu_job # Job name
#SBATCH -o gpu_job.o%j # Name of stdout output file(%j expands to jobId)
#SBATCH -e gpu_job.o%j # Name of stderr output file(%j expands to jobId)
#SBATCH -c 6 # Cores per task requested (1 task job)
#SBATCH -p gpu-shared
#SBATCH --gres=gpu # Options for requesting 1GPU
#SBATCH -t 10:10:00 # Run time (hh:mm:ss)
# Run the CUDA application

echo -e "Execution 0 : \n"

	echo "Small test"
	./dgesv0 1024

	echo "Medium test"
	./dgesv0 2048

	echo "Large test"
	./dgesv0 4096

echo -e "Execution 1 : \n"

	echo "Small test"
	./dgesv1 1024

	echo "Medium test"
	./dgesv1 2048

	echo "Large test"
	./dgesv1 4096

echo -e "Execution 2 : \n"
	echo "Small test"
	./dgesv2 1024

	echo "Medium test"
	./dgesv2 2048

	echo "Large test"
	./dgesv2 4096

echo -e "Execution 3 : \n"
	echo "Small test"
	./dgesv3 1024

	echo "Medium test"
	./dgesv3 2048

	echo "Large test"
	./dgesv3 4096

echo -e "Execution fast : \n"
	echo "Small test"
	./dgesvfast 1024

	echo "Medium test"
	./dgesvfast 2048

	echo "Large test"
	./dgesvfast 4096

echo -e "Execution ipo : \n"
	echo "Small test"
	./dgesvipo 1024

	echo "Medium test"
	./dgesvipo 2048

	echo "Large test"
	./dgesvipo 4096

echo -e "Execution pgo : \n"
	echo "Small test"
	./dgesvpgo 1024

	echo "Medium test"
	./dgesvpgo 2048

	echo "Large test"
	./dgesvpgo 4096

echo -e "Execution vector : \n"
	echo "Small test"
	./dgesvvect 1024

	echo "Medium test"
	./dgesvvect 2048

	echo "Large test"
	./dgesvvect 4096

echo -e "Execution para : \n"
	echo "Small test"
	./dgesvpara 1024

	echo "Medium test"
	./dgesvpara 2048

	echo "Large test"
	./dgesvpara 4096