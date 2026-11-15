//
// Created by PinkySmile on 29/03/2026.
//

#ifndef MIXRTS_SCBWUI_HPP
#define MIXRTS_SCBWUI_HPP


#include <map>
#include <filesystem>
#include <nlohmann/json_fwd.hpp>
#include <TGUI/Widgets/ScrollablePanel.hpp>
#include <TGUI/Widgets/Picture.hpp>
#include <TGUI/Widgets/Button.hpp>

#include "D2KCameo.hpp"
#include "forward.hpp"
#include "UI/UI.hpp"
#include "Sprite.hpp"
#include "Sound.hpp"
#include "Data/Player.hpp"


class SCBWUI : public UI {
private:
	bool _inMainMenu = true;
	std::string _prefix;
	std::string _modName;
	std::filesystem::path _base;

	tgui::Button::Ptr _resumeGame;
	tgui::Panel::Ptr _power;
	tgui::Button::Ptr _sell;
	tgui::Button::Ptr _guard;
	tgui::Button::Ptr _repair;
	tgui::Button::Ptr _retreat;
	tgui::Button::Ptr _world;
	tgui::Button::Ptr _up1;
	tgui::Button::Ptr _up2;
	tgui::Button::Ptr _down1;
	tgui::Button::Ptr _down2;
	tgui::Button::Ptr _options;
	tgui::Picture::Ptr _blazon;
	tgui::Picture::Ptr _greenPower;
	tgui::Picture::Ptr _yellowPower;
	tgui::Picture::Ptr _redPower;
	std::vector<std::string> _buildOrder;
	std::vector<std::string> _unitsOrder;
	tgui::ScrollablePanel::Ptr _buildQueue;
	tgui::ScrollablePanel::Ptr _unitsQueue;

	std::unordered_map<std::string, tgui::Texture> _cameos;
	std::array<tgui::Picture::Ptr, 8> _creditDigits;
	std::array<char, 8> _creditOldDigits{11, 11, 11, 11, 11, 11, 11, 11};
	std::array<tgui::Texture, 11> _creditRawDigits;

	std::vector<PlayerQueueEntry *> _buildingQueueEntries;
	std::vector<PlayerQueueEntry *> _unitsQueueEntries;

	std::vector<D2KCameo::Ptr> _buildQueueWidgets;
	std::vector<D2KCameo::Ptr> _unitsQueueWidgets;

	void _loadCameos();
	void _setupQueues();
	void _initPanel(const nlohmann::json &json);
	void _placeUiEvents();
	void _loadExtraAssets();
	void _setupCursorMapping();
	void _loadEvaSounds(const std::filesystem::path &base, const std::string &folder);
	void _getPanelObjects(const std::filesystem::path &path);
	void _createCameoWidgets();
	void _createCameoBuildWidgets();
	void _createCameoUnitsWidgets();

	void _updateQueueCameos();

protected:
	void _displaySelectedObjectUI(const GameObject &object) override;

public:
	SCBWUI(
		const Faction &faction,
		UIState *state,
		GameManager *manager,
		Player *owner,
		MapState *map,
		const std::filesystem::path &base,
		const nlohmann::json &params
	);
	~SCBWUI() noexcept override;
	void update() override;
	void render() override;
	void playEVA(EVASound sound, unsigned int expireIn, unsigned int priority, unsigned int cooldown, const std::string &args) override;
};



#endif //MIXRTS_SCBWUI_HPP
