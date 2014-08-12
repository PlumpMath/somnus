
#include <somnus/channel.hpp>

/**
 * This example shows the transfer of information from one yarn to another via a channel 
 *      with a std::shared_ptr type. The consumer yields if no data is in the channel. It resumes
 *      executing only when information is available.
 *
 * Output:
 *      [ ~1 second pause ]
 *      0
 *      1
 *      2
 *      3
 *      4
 *      5
 *      6
 *      7
 *      8
 *      9
 *      [ ~1 second pause ]
 */
int main(int argc, char* argv[])
{
    somnus::Channel<std::shared_ptr<int>> channel;

    auto producer = std::make_shared<somnus::Rope>();
    auto consumer = std::make_shared<somnus::Rope>();

    consumer->run([&] ()
    {
        for(int i=0; i < 10; ++i)
        {
            printf("%d\n", *(channel.pop()));
        }
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    producer->run([&] () 
    {
        for(int i = 0; i < 10; ++i)
        {
            channel.push(std::make_shared<int>(i));
        }
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0;
}
