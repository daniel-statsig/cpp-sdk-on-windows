#include <iostream>
#include <optional>
#include <statsig/statsig.h>
#include <statsig/statsig_types.h>
#include <nlohmann/json.hpp>
#include <thread>


using namespace statsig;

int main()
{
    std::optional<int> foo;

    StatsigUser user;
    user.user_id = "a-user";

    StatsigOptions opts;
    opts.output_logger_level = LogLevel::Debug;
    opts.logging_interval_ms = 10000;

    StatsigClient::Shared().InitializeAsync("client-rfLvYGag3eyU0jYW5zcIJTQip7GXxSrhOFN69IGMjvq", [](auto result){
        std::cout << "Init: " << result << std::endl;
      
        FeatureGate gate = StatsigClient::Shared().GetFeatureGate("a_gate");
        std::cout << "a_gate: (" << gate.GetEvaluationDetails().reason << ") " << std::to_string(gate.GetValue()) << std::endl;

    /*    StatsigClient::Shared().UpdateUserAsync(StatsigUser{ "b-user" }, [](auto upResult) {
            std::cout << "Update: " << upResult << std::endl;

            });*/
        
        }, user, opts);


    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

