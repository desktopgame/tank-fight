#include "PlayResult.hpp"
PlayResult::PlayResult() : scoreTable(), currentScore(0) {
}

void PlayResult::record(int score) {
	scoreTable.insert(score);
	this->currentScore = score;
}

std::optional<gel::IntegerScore> PlayResult::getScoreAt(int index) const {
	return (scoreTable.at(index));
}

int PlayResult::getCurrentScore() const {
	return currentScore;
}

int PlayResult::getTableLength() const {
	return 10;
}