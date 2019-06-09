#ifndef GAME_SCENE_RESULTSCENE_HPP
#define GAME_SCENE_RESULTSCENE_HPP
#include "../PlayResult.hpp"
#include "../../gel/gel.hpp"
#include <memory>
class ResultScene : public gel::IScene {
	public:
	explicit ResultScene(const std::shared_ptr<gel::TextureManager>& textureManager, PlayResult& playResult);
	void show() override;
	void update() override;
	void draw() override;
	void hide() override;
	bool isFinished() const override;
	std::string getNextScene() const override;
	private:
	std::shared_ptr<gel::TextureManager> textureManager;
	gel::Timer yourScoreTimer;
	gel::Timer isTimer;
	gel::Timer scoreTimer;
	gel::Number scoreNum;
	int phase;
	PlayResult& playResult;
	bool finished;
};
#endif