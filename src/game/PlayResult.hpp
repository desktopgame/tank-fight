#ifndef GAME_PLAYRESULT_HPP
#define GAME_PLAYRESULT_HPP
#include "../gel/gel.hpp"
#include <optional>
class PlayResult {
	public:
	explicit PlayResult();

	void record(int score);
	std::optional<gel::IntegerScore> getScoreAt(int index) const;
	int getCurrentScore() const;
	int getTableLength() const;

	private:
	gel::ScoreTable<gel::IntegerScore, 10> scoreTable;
	int currentScore;
};
#endif