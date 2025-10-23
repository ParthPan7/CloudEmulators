#include <jitter_orchestrator/Scheduler.hpp>
#include <memory>
#include <iostream>
namespace clog::jitter_orchestrator
{
	
	void Scheduler::addTask(std::shared_ptr<IJitterCommand> command, int intervalSec)
	{
		auto task = std::make_shared<Task>();
		task->command = command;
		task->intervalSec = intervalSec;
		task->running = false;

		std::lock_guard<std::mutex> lock(_taskMutex);
		_tasks.push_back(task);
	}

	void Scheduler::start()
	{
		_schedulerRunning = true;

		std::lock_guard<std::mutex> lock(_taskMutex);
		for (auto& task: _tasks)
		{
			task->running = true;
			task->worker = std::thread([task]() 
			{
				while (task->running)
				{
					auto start = std::chrono::steady_clock::now();
					try
					{
						task->command->execute();
					}
					catch (const std::exception& e)
					{
						std::cerr << "[Scheduler] Exception :" << e.what() << '\n';
					}
					std::this_thread::sleep_until(start + std::chrono::seconds(task->intervalSec));
				}
			});
		}
	}

	void Scheduler::stop()
	{
		_schedulerRunning = false;
		std::lock_guard<std::mutex> lock(_taskMutex);
		for (auto& task: _tasks)
		{
			if (task->running)
			{
				task->running = false;
				if (task->worker.joinable())
				{
					task->worker.join();
				}
			}
		}
	}
};