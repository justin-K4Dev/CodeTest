#include "stdafx.h"
#include "TestFunction.h"

///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-20-2012 23:12:38
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <agents.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

#pragma optimize( "", off )
// Simulates work by performing a long spin loop.
void spin_loop()
{
	for (int i = 0; i < 500000000; ++i)
	{
	}
}
#pragma optimize( "", on )

// Agent that performs some work and then yields the current context.
class work_yield_agent : public Concurrency::agent
{
private:
	// The group number that the agent belongs to.
	unsigned int _group_number;
	// A task number that is associated with the agent.
	unsigned int _task_number;

public:
	explicit work_yield_agent( unsigned int group_number, unsigned int task_number )
	: _group_number(group_number) , _task_number(task_number)
	{
	}

	explicit work_yield_agent(Concurrency::Scheduler& scheduler,
		                      unsigned int group_number, unsigned int task_number)
	: agent(scheduler) , _group_number(group_number) , _task_number(task_number)
	{
	}

	explicit work_yield_agent(Concurrency::ScheduleGroup& group,
		                      unsigned int group_number, unsigned int task_number)
	: agent(group) , _group_number(group_number) , _task_number(task_number)
	{
	}

protected:
	// Performs the work of the agent.   
	void run()
	{
		std::wstringstream header, ss;

		// Create a string that is prepended to each message.
		header << L"group " << _group_number << L",task " << _task_number << L": ";

		// Perform work.
		ss << header.str() << L"first loop..." << std::endl;
		std::wcout << ss.str();
		spin_loop();

		// Cooperatively yield the current context. 
		// The task scheduler will then run all blocked contexts.
		ss = std::wstringstream();
		ss << header.str() << L"waiting..." << std::endl;
		std::wcout << ss.str();
		Concurrency::wait(0);

		// Perform more work.
		ss = std::wstringstream();
		ss << header.str() << L"second loop..." << std::endl;
		std::wcout << ss.str();
		spin_loop();

		// Print a final message and then set the agent to the 
		// finished state.
		ss = std::wstringstream();
		ss << header.str() << L"finished..." << std::endl;
		std::wcout << ss.str();

		done();
	}  
};

// Creates and runs several groups of agents. Each group of agents is associated 
// with a different schedule group.
void run_agents()
{
	// The number of schedule groups to create.
	const unsigned int group_count = 2;
	// The number of agent to create per schedule group.
	const unsigned int tasks_per_group = 2;

	// A collection of schedule groups.
	std::vector<Concurrency::ScheduleGroup*> groups;
	// A collection of agents.
	std::vector<Concurrency::agent*> agents;

	// Create a series of schedule groups. 
	for (unsigned int group = 0; group < group_count; ++group)
	{
		groups.push_back(Concurrency::CurrentScheduler::CreateScheduleGroup());

		// For each schedule group, create a series of agents.
		for (unsigned int task = 0; task < tasks_per_group; ++task)
		{
			// Add an agent to the collection. Pass the current schedule 
			// group to the work_yield_agent constructor to schedule the agent
			// in this group.
			agents.push_back(new work_yield_agent(*groups.back(), group, task));
		}
	}

	// Start each agent.
	std::for_each( agents.begin(), agents.end(), [](Concurrency::agent* a) 
	                                             {
		                                             a->start();
	                                             } );

	// Wait for all agents to finsih.
	Concurrency::agent::wait_for_all( agents.size(), &agents[0] );

	// Free the memory that was allocated for each agent.
	std::for_each( agents.begin(), agents.end(), [](Concurrency::agent* a) 
	                                             {
													 delete a;
												 } );

	// Release each schedule group.
	std::for_each( groups.begin(), groups.end(), [](Concurrency::ScheduleGroup* group)
												 {
													 group->Release();
												 } );
}

///////////////////////////////////////////////////////////////////////////////
/// @file ConRT_TaskScheduler.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-20-2012 23:12:45
///////////////////////////////////////////////////////////////////////////////

void TestPPL_TaskScheduler()
{
	{
		// Run the agents two times. Each run uses a scheduler
		// policy that limits the maximum number of processing resources to two.

		// The first run uses the EnhanceScheduleGroupLocality 
		// scheduling protocol. 
		std::wcout << L"Using EnhanceScheduleGroupLocality..." << std::endl;
		Concurrency::CurrentScheduler::Create(Concurrency::SchedulerPolicy(3, 
											  Concurrency::MinConcurrency, 1,
											  Concurrency::MaxConcurrency, 2,
											  Concurrency::SchedulingProtocol, Concurrency::EnhanceScheduleGroupLocality));

		run_agents();
		Concurrency::CurrentScheduler::Detach();

		std::wcout << std::endl << std::endl;

		// The second run uses the EnhanceForwardProgress 
		// scheduling protocol. 
		std::wcout << L"Using EnhanceForwardProgress..." << std::endl;
		Concurrency::CurrentScheduler::Create(Concurrency::SchedulerPolicy(3, 
											  Concurrency::MinConcurrency, 1,
											  Concurrency::MaxConcurrency, 2,
											  Concurrency::SchedulingProtocol, Concurrency::EnhanceForwardProgress));

		run_agents();
		Concurrency::CurrentScheduler::Detach();

		_getch();
	}
}