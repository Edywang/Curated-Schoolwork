
/*
 * Name: Edwin Wang
 * CruzID: ekwang
 * Assignment: 12B pa4
 * Date: 5/12/2019
 * Description: Main method
 */

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Simulation {

	public static void main(String[] args) throws IOException {
		Scanner in = new Scanner(new File(args[0]));
		PrintWriter rptout;
		PrintWriter trcout;
		rptout = new PrintWriter(new FileWriter(args[0] + ".rpt"));
		trcout = new PrintWriter(new FileWriter(args[0] + ".trc"));
		int numJobs = in.nextInt(); // numJobs - 1 = numQueues
		int arrivalTime;
		int time;
		int maxWait;
		int totalWait;
		int index = 0;
		Job job;
		Job[] jobStorage = new Job[numJobs];
		while (in.hasNextInt()) {
			arrivalTime = in.nextInt();
			jobStorage[index] = new Job(arrivalTime, in.nextInt());
			++index;
		}
		Queue[] queues = new Queue[numJobs];

		for (int i = 0; i < numJobs; ++i) {
			queues[i] = new Queue();
			queues[0].enqueue(jobStorage[i]);
		}

		// report and trace file heading
		trcout.println("Trace file: " + args[0] + ".trc");
		trcout.printf("%d Job%s:\n", numJobs, numJobs == 1 ? "" : "s");
		trcout.println(queues[0] + "\n");
		rptout.println("Report file: " + args[0] + ".rpt");
		rptout.printf("%d Job%s:\n", numJobs, numJobs == 1 ? "" : "s");
		rptout.println(queues[0] + "\n");
		rptout.println("***********************************************************");

		for (int numProcessors = 1; numProcessors < numJobs; ++numProcessors) {

			// Full Reset
			totalWait = 0;
			maxWait = 0;
			time = 1;
			queues = reset(queues, jobStorage);

			// Print weird asterisk and processor thing
			trcout.println("*****************************");
			trcout.printf("%d processor%s:\n", numProcessors, numProcessors == 1 ? "" : "s");
			trcout.println("*****************************");
			trcout.println("time=0");
			for (int j = 0; j < numProcessors + 1; ++j) {
				trcout.println(j + ": " + queues[j]);
			}
			trcout.println();

			// Process
			while (!completed(queues, numJobs)) {
				// Reset job for time
				job = null;
				for (int currentProcessor = 1; currentProcessor <= numProcessors; ++currentProcessor) {
					if (!queues[currentProcessor].isEmpty()) {
						if (((Job) queues[currentProcessor].peek()).getFinish() == Job.UNDEF)
							((Job) queues[currentProcessor].peek()).computeFinishTime(time);
						while (((Job) queues[currentProcessor].peek()).getFinish() == time) {
							job = (Job) queues[currentProcessor].dequeue();
							if (job.getFinish() - job.getArrival() - job.getDuration() > maxWait)
								maxWait = job.getFinish() - job.getArrival() - job.getDuration();
							totalWait += job.getFinish() - job.getArrival() - job.getDuration();
							queues[0].enqueue(job);
							if (queues[currentProcessor].isEmpty())
								break;
							if (((Job) queues[currentProcessor].peek()).getFinish() == Job.UNDEF)
								((Job) queues[currentProcessor].peek()).computeFinishTime(time);
							if (((Job) queues[currentProcessor].peek()).getFinish() != time)
								break;

						}
					}
				}
				if (!queues[0].isEmpty())
					while (((Job) queues[0].peek()).getFinish() == Job.UNDEF
							&& ((Job) queues[0].peek()).getArrival() == time) {
						job = (Job) queues[0].dequeue();
						shortest(queues, numProcessors).enqueue(job);
						if (queues[0].isEmpty())
							break;
					}
				for (int currentProcessor = 1; currentProcessor <= numProcessors; ++currentProcessor) {
					if (!queues[currentProcessor].isEmpty()) {
						if (((Job) queues[currentProcessor].peek()).getFinish() == Job.UNDEF)
							((Job) queues[currentProcessor].peek()).computeFinishTime(time);
						while (((Job) queues[currentProcessor].peek()).getFinish() == time) {
							job = (Job) queues[currentProcessor].dequeue();
							if (job.getFinish() - job.getArrival() - job.getDuration() > maxWait)
								maxWait = job.getFinish() - job.getArrival() - job.getDuration();
							totalWait += job.getFinish() - job.getArrival() - job.getDuration();
							queues[0].enqueue(job);
							if (queues[currentProcessor].isEmpty())
								break;
							if (((Job) queues[currentProcessor].peek()).getFinish() == Job.UNDEF)
								((Job) queues[currentProcessor].peek()).computeFinishTime(time);
							if (((Job) queues[currentProcessor].peek()).getFinish() != time)
								break;

						}
					}
				}
				// Print trace
				if (job != null) {
					trcout.println("time=" + time);
					for (int j = 0; j < numProcessors + 1; ++j) {
						trcout.println(j + ": " + queues[j]);
					}
					trcout.println();
				}
				++time;
			}
			// Print report
			rptout.printf("%d processor%s: totalWait=%d, maxWait=%d, averageWait=%.2f\n", numProcessors,
					numProcessors == 1 ? "" : "s", totalWait, maxWait, (float) totalWait / numJobs);
		}

		// Closing scanners
		in.close();
		trcout.close();
		rptout.close();

	}

	// completed()
	// returns false if there are still jobs to be processed, true otherwise
	// Error in here!
	private static boolean completed(Queue[] queues, int numJobs) {
		if (queues[0].length() == numJobs) {
			if (((Job) queues[0].peek()).getFinish() != Job.UNDEF) {
				return true;
			}
		}
		return false;
	}

	// shortest()
	// returns shortest Queue closest to index 1 excluding 0
	private static Queue shortest(Queue[] queues, int numProcessors) {
		int index = 1;
		for (int i = 1; i < numProcessors + 1; ++i)
			if (queues[i].length() < queues[index].length())
				index = i;
		return queues[index];
	}

	// reset()
	// returns new Queue array with one more Queue and reset jobs
	private static Queue[] reset(Queue[] queues, Job[] storage) {
		queues[0].dequeueAll();
		for (int i = 0; i < storage.length; ++i) {
			storage[i].resetFinishTime();
			queues[0].enqueue(storage[i]);
		}
		return queues;
	}
}
