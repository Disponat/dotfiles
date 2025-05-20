class State {
public:
  double score = 0;

  void init(){};
  void transition(){};
  void back(){};
};

constexpr int INF = 1e9;

unsigned int randxor() { // produces random integers
    static unsigned int x=123456789,y=362436069,z=521288629,w=88675123;
    unsigned int t;
    t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );
}

struct TimeKeeper {
    std::chrono::high_resolution_clock::time_point start_time;
    int64_t time_threshold;
    TimeKeeper(const int64_t &time_threshold_) : start_time(std::chrono::high_resolution_clock::now()), time_threshold(time_threshold_) {}
    
    bool is_timeover() const {
        auto diff = std::chrono::high_resolution_clock::now() - this->start_time;
        return std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() >= time_threshold;
    }

    int64_t elapsed_ms() const {
        auto diff = std::chrono::high_resolution_clock::now() - this->start_time;
        return std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
    }
};

State simulatedAnnealing(double start_temp, double end_temp, const TimeKeeper& timekeeper) {
    State now_state;
    now_state.init();
    int now_score = now_state.score;
    int best_score = now_score;
    auto best_state = now_state;
    // mt19937 mt_for_action(0);
    int INF = INT_MAX;
    while (!timekeeper.is_timeover()) {
        now_state.transition();
        int next_score = now_state.score;

        double temp = start_temp + (end_temp - start_temp) * ((double)timekeeper.elapsed_ms()/timekeeper.time_threshold);
		    // double temp = end_temp + start_temp*exp(-(double)timekeeper.elapsed_ms()/10.0);

        double probability = exp((next_score-now_score)/temp);
        bool is_force_next = probability > (randxor() % INF)/(double)(INF);

        if (next_score > now_score || is_force_next) {
            now_score = next_score;
        }
        else {
            now_state.back();
        }

        if (next_score > best_score) {
            best_score = next_score;
            best_state = now_state;
        }
    }
    
    // cout << "# t_num:  " << set_t.count() << endl;
    // cout << "# t_score:" << best_score << endl;
    return best_state;
}

