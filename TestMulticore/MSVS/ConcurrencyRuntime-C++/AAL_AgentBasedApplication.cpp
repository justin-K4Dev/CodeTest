#include "stdafx.h"
#include "TestFunction.h"


///////////////////////////////////////////////////////////////////////////////
/// @author justin
/// @date 8-21-2012 0:36:13
/// @brief 
///
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <windows.h>
#include <agents.h>
#include <string>

// This agent writes a string to its target and reads an integer
// from its source.
class agent1 : public Concurrency::agent 
{
public:
   explicit agent1(Concurrency::ISource<int>& source, Concurrency::ITarget<std::string>& target)
      : _source(source)
      , _target(target)
   {
   }

protected:
	void run()
	{
		// Send the request.
		Concurrency::send( _target, std::string( "request" ) );
		std::cout << "agent1: Sending Request !!!" << std::endl;

		// Read the response.
		int response = Concurrency::receive( _source );  
		std::cout << "agent2: Received " << response << std::endl;

		// Signal Completion
		done();
    }

private:   
   Concurrency::ISource<int>& _source;
   Concurrency::ITarget<std::string>& _target;
};

// This agent reads a string to its source and then writes an integer
// to its target.
class agent2 : public Concurrency::agent 
{
public:
   explicit agent2(Concurrency::ISource<std::string>& source, Concurrency::ITarget<int>& target)
      : _source(source)
      , _target(target)
   {
   }

protected:
   void run()
   {
        // Read the request.
	    std::string request = Concurrency::receive( _source );  
		std::cout << "agent1: Received " << request << std::endl;

		// Send the response.
		Concurrency::send( _target, 42 );
		std::cout << "agent1: Sending Response !!!" << std::endl;

		// Signal Completion
		this->done();
   }

private:   
   Concurrency::ISource<std::string>& _source;
   Concurrency::ITarget<int>& _target;
};


///////////////////////////////////////////////////////////////////////////////
/// @file TestAAL_AgentBasedApplication.cpp
/// @brief 
/// @return
/// @param 
/// 
/// @author justin
/// @date 8-21-2012 0:36:22
///////////////////////////////////////////////////////////////////////////////

void TestAAL_AgentBasedApplication()
{
	// 기본 예제
	{
		// Step 1: Create two message buffers to serve as communication channels
		// between the agents.

		// The first agent writes messages to this buffer; the second
		// agents reads messages from this buffer.

		// Declare the unbounded buffer below
		Concurrency::unbounded_buffer< std::string > buffer1;

		// The first agent reads messages from this buffer; the second
		// agents writes messages to this buffer.

		// Declare the overwrite buffer below
		Concurrency::overwrite_buffer< int > buffer2;

		// Step 2: Create the agents.
		agent1 first_agent( buffer2, buffer1 );
		agent2 second_agent( buffer1, buffer2 );

		// Step 3: Start the agents. The runtime calls the run method on
		// each agent.
		first_agent.start();  
		second_agent.start();  

		// Step 4: Wait for both agents to finish.
		Concurrency::agent::wait( &first_agent );  
		Concurrency::agent::wait( &second_agent );

		_getch();
	}
}