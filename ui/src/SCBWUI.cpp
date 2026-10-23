//
// Created by PinkySmile on 29/03/2026.
//

#include <nlohmann/json.hpp>
#include "SCBWUI.hpp"
#include "D2KCameo.hpp"
#include "UI/UI.hpp"
#include "Resources/Assert.hpp"
#include "Data/Faction.hpp"
#include "Data/Mod.hpp"
#include "Data/Player.hpp"
#include "Resources/Game.hpp"
#include "Data/Animation.hpp"
#include "Data/GameManager.hpp"

static std::string __buildOrder[] = {
	"command_center",
	"comsat_station",
	"nuclear_silo",
	"supply_depot",
	"refinery",
	"barracks",
	"engineering_bay",
	"bunker",
	"academy",
	"missile_turret",

	"factory",
	"machine_shop",
	"starport",
	"control_tower",
	"armory",
	"science_facility",
	"physics_lab",
	"covert_ops"
};
static std::string __unitsOrder[] = {
	"scv",
	"marine",
	"firebat",
	"medic",
	"ghost",

	"vulture",
	"spider_mine",
	"siege_tank",
	"goliath",

	"wraith",
	"science_vessel",
	"dropship",
	"battlecruiser",
	"valkyrie"
};

void SCBWUI::_loadEvaSounds(const std::filesystem::path &base, const std::string &folder)
{
	/*this->_evaSounds[EVA_BUILDING]         .load(base / "announcers" / game->locale / folder / "build.ogg", false);
	this->_evaSounds[EVA_BUILDING_DONE]    .load(base / "announcers" / game->locale / folder / "building_done.ogg", false);
	this->_evaSounds[EVA_BUILDING_LOST]    .load(base / "announcers" / game->locale / folder / "building_lost.ogg", false);
	this->_evaSounds[EVA_CANCEL]           .load(base / "announcers" / game->locale / folder / "cancel.ogg", false);
	this->_evaSounds[EVA_CANNOT_DEPLOY]    .load(base / "announcers" / game->locale / folder / "cannot_deploy.ogg", false);
	this->_evaSounds[EVA_CANNOT_BUILD]     .load(base / "announcers" / game->locale / folder / "cannot_place.ogg", false);
	this->_evaSounds[EVA_GUARDING]         .load(base / "announcers" / game->locale / folder / "guarding.ogg", false);
	this->_evaSounds[EVA_HOLD_QUEUE]       .load(base / "announcers" / game->locale / folder / "hold.ogg", false);
	this->_evaSounds[EVA_LOST]             .load(base / "announcers" / game->locale / folder / "lose.ogg", false);
	this->_evaSounds[EVA_WON]              .load(base / "announcers" / game->locale / folder / "win.ogg", false);
	this->_evaSounds[EVA_LOW_POWER]        .load(base / "announcers" / game->locale / folder / "low_power.ogg", false);
	this->_evaSounds[EVA_UNLOCKED]         .load(base / "announcers" / game->locale / folder / "new_unlock.ogg", false);
	this->_evaSounds[EVA_NO_CREDITS]       .load(base / "announcers" / game->locale / folder / "no_money.ogg", false);
	this->_evaSounds[EVA_PRIMARY_SELECTED] .load(base / "announcers" / game->locale / folder / "primary.ogg", false);
	this->_evaSounds[EVA_RETREAT]          .load(base / "announcers" / game->locale / folder / "retreat.ogg", false);
	this->_evaSounds[EVA_SELL]             .load(base / "announcers" / game->locale / folder / "sell.ogg", false);
	this->_evaSounds[EVA_TRAINING]         .load(base / "announcers" / game->locale / folder / "train.ogg", false);
	this->_evaSounds[EVA_UNIT_READY]       .load(base / "announcers" / game->locale / folder / "unit_ready.ogg", false);
	this->_evaSounds[EVA_UPGRADING]        .load(base / "announcers" / game->locale / folder / "upgrading.ogg", false);
	this->_evaSounds[EVA_REQUIRE_STORAGE]  .load(base / "announcers" / game->locale / folder / "silo_needed.ogg", false);
	this->_evaSounds[EVA_UNIT_LOST]        .load(base / "announcers" / game->locale / folder / "unit_lost.ogg", false);
	this->_evaSounds[EVA_HARV_UNDER_ATTACK].load(base / "announcers" / game->locale / folder / "harvester_attacked.ogg", false);
	this->_evaSounds[EVA_BUILDING_ATTACKED].load(base / "announcers" / game->locale / folder / "building_attacked.ogg", false);
	this->_evaSounds[EVA_BUILDING_CAPTURED].load(base / "announcers" / game->locale / folder / "captured.ogg", false);
	this->_evaSounds[EVA_HAZARD_SPAWNED]   .load(base / "announcers" / game->locale / folder / "worm_sign.ogg", false);
	this->_evaSounds[EVA_HAZARD_ATTACKED]  .load(base / "announcers" / game->locale / folder / "worm_attack.ogg", false);
	this->_evaSounds[EVA_ORDER_PLACED]     .load(base / "announcers" / game->locale / folder / "order_placed.ogg", false);
	this->_evaSounds[EVA_ORDER_IN_1]       .load(base / "announcers" / game->locale / folder / "1min_left.ogg", false);
	this->_evaSounds[EVA_ORDER_IN_2]       .load(base / "announcers" / game->locale / folder / "2min_left.ogg", false);
	this->_evaSounds[EVA_ORDER_IN_3]       .load(base / "announcers" / game->locale / folder / "3min_left.ogg", false);
	this->_evaSounds[EVA_ORDER_IN_4]       .load(base / "announcers" / game->locale / folder / "4min_left.ogg", false);
	this->_evaSounds[EVA_ORDER_IN_5]       .load(base / "announcers" / game->locale / folder / "5min_left.ogg", false);
	this->_evaSounds[EVA_CASH_DOWN]        .load(base / "sounds/CASHTIK1.ogg", false);
	this->_evaSounds[EVA_CASH_UP]          .load(base / "sounds/CASHTIK1.ogg", false);
	this->_evaSounds[EVA_POWER_OFF]        .load(base / "sounds/POWRDN1.ogg", false);
	this->_evaSounds[EVA_POWER_ON]         .load(base / "sounds/POWRUP1.ogg", false);
	this->_evaSounds[EVA_RADAR_UP]         .load(base / "sounds/RADRON1.ogg", false);*/
}

void SCBWUI::_setupCursorMapping()
{
	this->_cursorMapping[CURSOR_NORMAL]                 = "arrow";
	this->_cursorMapping[CURSOR_START_SELECT]           = "drag";
	this->_cursorMapping[CURSOR_MOVE]                   = "mag_g";
	this->_cursorMapping[CURSOR_MOVE_RESTRICT]          = "mag_g";
	this->_cursorMapping[CURSOR_NO_MOVE]                = "illegal";
	this->_cursorMapping[CURSOR_SELECT]                 = "arrow";
	this->_cursorMapping[CURSOR_HARVEST]                = "mag_y";
	this->_cursorMapping[CURSOR_ATTACK]                 = "mag_r";
	this->_cursorMapping[CURSOR_ATTACK_MOVE]            = ""; // TODO:
	this->_cursorMapping[CURSOR_ENTER]                  = "mag_r";
	this->_cursorMapping[CURSOR_DUMP]                   = "mag_g";
	this->_cursorMapping[CURSOR_SCROLL_ALL_DIRS]        = ""; // TODO:
	this->_cursorMapping[CURSOR_SCROLL_RIGHT]           = "scroll_r";
	this->_cursorMapping[CURSOR_SCROLL_LEFT]            = "scroll_l";
	this->_cursorMapping[CURSOR_SCROLL_TOP]             = "scroll_t";
	this->_cursorMapping[CURSOR_SCROLL_TOP_RIGHT]       = "scroll_tr";
	this->_cursorMapping[CURSOR_SCROLL_TOP_LEFT]        = "scroll_tl";
	this->_cursorMapping[CURSOR_SCROLL_BOTTOM]          = "scroll_b";
	this->_cursorMapping[CURSOR_SCROLL_BOTTOM_RIGHT]    = "scroll_br";
	this->_cursorMapping[CURSOR_SCROLL_BOTTOM_LEFT]     = "scroll_bl";
	this->_cursorMapping[CURSOR_NO_SCROLL_TOP]          = "scroll_t";
	this->_cursorMapping[CURSOR_NO_SCROLL_TOP_RIGHT]    = "scroll_tr";
	this->_cursorMapping[CURSOR_NO_SCROLL_TOP_LEFT]     = "scroll_tl";
	this->_cursorMapping[CURSOR_NO_SCROLL_BOTTOM]       = "scroll_b";
	this->_cursorMapping[CURSOR_NO_SCROLL_BOTTOM_RIGHT] = "scroll_br";
	this->_cursorMapping[CURSOR_NO_SCROLL_BOTTOM_LEFT]  = "scroll_bl";
	this->_cursorMapping[CURSOR_NO_SCROLL_RIGHT]        = "scroll_r";
	this->_cursorMapping[CURSOR_NO_SCROLL_LEFT]         = "scroll_l";
	this->_cursorMapping[CURSOR_DEPLOY]                 = "mag_g";
	this->_cursorMapping[CURSOR_NO_DEPLOY]              = "arrow";
}

void SCBWUI::_getPanelObjects(const std::filesystem::path &path)
{
	this->_panel->loadWidgetsFromFile(path.native());
	this->_sell            = this->_panel->get<tgui::Button>("Sell");
	this->_guard           = this->_panel->get<tgui::Button>("Guard");
	this->_repair          = this->_panel->get<tgui::Button>("Repair");
	this->_retreat         = this->_panel->get<tgui::Button>("Retreat");
	this->_world           = this->_panel->get<tgui::Button>("Map");
	this->_up1             = this->_panel->get<tgui::Button>("Up1");
	this->_up2             = this->_panel->get<tgui::Button>("Up2");
	this->_down1           = this->_panel->get<tgui::Button>("Down1");
	this->_down2           = this->_panel->get<tgui::Button>("Down2");
	this->_options         = this->_panel->get<tgui::Button>("Options");
	this->_blazon          = this->_panel->get<tgui::Picture>("Blazon");
	this->_power           = this->_panel->get<tgui::Panel>("Power");
	this->_settings        = this->_panel->get<tgui::Panel>("Settings");
	this->_greenPower      = this->_power->get<tgui::Picture>("GreenPower");
	this->_yellowPower     = this->_power->get<tgui::Picture>("YellowPower");
	this->_redPower        = this->_power->get<tgui::Picture>("RedPower");
	this->_buildQueue      = this->_panel->get<tgui::ScrollablePanel>("BuildingQueue");
	this->_unitsQueue      = this->_panel->get<tgui::ScrollablePanel>("UnitsQueue");
	this->_creditDigits[0] = this->_panel->get<tgui::Picture>("Credit0");
	this->_creditDigits[1] = this->_panel->get<tgui::Picture>("Credit1");
	this->_creditDigits[2] = this->_panel->get<tgui::Picture>("Credit2");
	this->_creditDigits[3] = this->_panel->get<tgui::Picture>("Credit3");
	this->_creditDigits[4] = this->_panel->get<tgui::Picture>("Credit4");
	this->_creditDigits[5] = this->_panel->get<tgui::Picture>("Credit5");
	this->_creditDigits[6] = this->_panel->get<tgui::Picture>("Credit6");
	this->_creditDigits[7] = this->_panel->get<tgui::Picture>("Credit7");
	this->_resumeGame      = this->_settings->get<tgui::Button>("Resume");
}

void SCBWUI::_initPanel(const nlohmann::json &json)
{
	this->_blazon->getRenderer()->setTexture({(this->_base / json["blazon"].get<std::string>()).native()});
	this->_settings->setVisible(false);
	this->_buildQueue->getVerticalScrollbar()->setScrollAmount(47);
	this->_unitsQueue->getVerticalScrollbar()->setScrollAmount(47);
}

void SCBWUI::_placeUiEvents()
{
	this->_up1->onMousePress([this] {
		this->_buildQueue->scrolled(1, {0, 0}, false);
	});
	this->_up2->onMousePress([this] {
		this->_unitsQueue->scrolled(1, {0, 0}, false);
	});
	this->_down1->onMousePress([this] {
		this->_buildQueue->scrolled(-1, {0, 0}, false);
	});
	this->_down2->onMousePress([this] {
		this->_unitsQueue->scrolled(-1, {0, 0}, false);
	});
	this->_options->onMousePress([this]{
	});
	this->_options->onClick([]{
		game->paused = true;
	});
	this->_resumeGame->onMousePress([this]{
	});
	this->_resumeGame->onClick([]{
		game->paused = false;
	});
}

void SCBWUI::_loadExtraAssets()
{
	this->_creditRawDigits[0] = tgui::Texture{(this->_base / "ui/numbers/credit_0.png").native()};
	this->_creditRawDigits[1] = tgui::Texture{(this->_base / "ui/numbers/credit_1.png").native()};
	this->_creditRawDigits[2] = tgui::Texture{(this->_base / "ui/numbers/credit_2.png").native()};
	this->_creditRawDigits[3] = tgui::Texture{(this->_base / "ui/numbers/credit_3.png").native()};
	this->_creditRawDigits[4] = tgui::Texture{(this->_base / "ui/numbers/credit_4.png").native()};
	this->_creditRawDigits[5] = tgui::Texture{(this->_base / "ui/numbers/credit_5.png").native()};
	this->_creditRawDigits[6] = tgui::Texture{(this->_base / "ui/numbers/credit_6.png").native()};
	this->_creditRawDigits[7] = tgui::Texture{(this->_base / "ui/numbers/credit_7.png").native()};
	this->_creditRawDigits[8] = tgui::Texture{(this->_base / "ui/numbers/credit_8.png").native()};
	this->_creditRawDigits[9] = tgui::Texture{(this->_base / "ui/numbers/credit_9.png").native()};
	this->_creditRawDigits[10]= tgui::Texture{(this->_base / "ui/numbers/credit_empty.png").native()};
	for (size_t i = 0; i < this->_selectCorners.size(); i++)
		assert_exp(this->_selectCorners[i].loadFromFile(this->_base / ("cursor/select_" + std::to_string(i) + ".png")));
}

void SCBWUI::_loadCameos()
{
	auto start = this->_modName;

	start.push_back(':');
	this->_buildOrder.reserve(std::size(__buildOrder));
	for (auto &b : __buildOrder)
		this->_buildOrder.push_back(start + b);
	this->_unitsOrder.reserve(std::size(__unitsOrder));
	for (auto &u : __unitsOrder)
		this->_unitsOrder.push_back(start + u);
	for (const auto &entry : std::filesystem::directory_iterator(this->_base / "cameos")) {
		if (entry.is_directory())
			continue;

		const auto &entryPath = entry.path();
		auto name = entryPath.filename().stem().string();

		this->_cameos[start + name] = tgui::Texture{entryPath.native(), {}, {}, true};
	}
}

void SCBWUI::_setupQueues()
{
	const char *bs[] = {
		"scv",
		"engineering_bay",
		"armory",
		"academy",
		"covert_ops",
		"machine_shop",
		"science_facility",
		"control_tower",
		"physics_lab"
	};
	const char *us[] = {
		"command_center",
		"barracks",
		"factory"
	};
	std::vector<PlayerQueue *> bq;
	std::vector<PlayerQueue *> uq;
	std::string start = this->_modName;

	start.push_back(':');
	for (const char *b : bs) {
		if (this->ownerState->queues.contains(start + b))
			bq.push_back(&this->ownerState->queues.at(start + b));
		else
			bq.push_back(nullptr);
	}
	for (const char *u : us) {
		if (this->ownerState->queues.contains(start + u))
			uq.push_back(&this->ownerState->queues.at(start + u));
		else
			uq.push_back(nullptr);
	}

	this->_buildingQueueEntries.reserve(this->_buildOrder.size());
	for (const auto &b : this->_buildOrder) {
		bool found = false;

		for (auto &q : bq) {
			if (!q || !q->entries.contains(b))
				continue;
			this->_buildingQueueEntries.push_back(&q->entries.at(b));
			found = true;
			break;
		}
		if (!found)
			this->_buildingQueueEntries.push_back(nullptr);
	}

	this->_unitsQueueEntries.reserve(this->_unitsOrder.size());
	for (auto &u : this->_unitsOrder) {
		bool found = false;

		for (auto &q : uq) {
			if (!q || !q->entries.contains(u))
				continue;
			this->_unitsQueueEntries.push_back(&q->entries.at(u));
			found = true;
			break;
		}
		if (!found)
			this->_unitsQueueEntries.push_back(nullptr);
	}
}

void SCBWUI::_createCameoBuildWidgets()
{
	std::string prefixedStart = this->_modName;
	std::string last;

	prefixedStart.push_back(':');
	prefixedStart += this->_prefix;
	prefixedStart.push_back('_');
	for (size_t i = 0; i < this->_buildOrder.size(); i++) {
		auto &b = this->_buildOrder[i];
		std::string realName;
		std::string name = b.substr(b.find(':') + 1);

		if (name == "barr" || name == "lfac" || name == "hfac")
			realName = prefixedStart + name;
		else
			realName = b;

		auto pic = D2KCameo::create(this->_base);
		auto r = pic->getRenderer();
		auto size = this->_cameos[b].getImageSize();

		pic->setSize("&.w", size.y + 1);
		pic->onMousePress([this, realName, i]{
			if (this->_buildingQueueEntries[i]->buildProgress == this->_buildingQueueEntries[i]->buildTime)
				this->selectBuildingForPlacement(realName);
			else
				this->_eventQueue.emplace_back(StartBuildEvent{realName, *this->_buildingQueueEntries[i]->queueId});
		});
		pic->onRightMousePress([this, realName, i]{
			this->_eventQueue.emplace_back(CancelBuildEvent{realName, *this->_buildingQueueEntries[i]->queueId});
			this->_placementBuilding = nullptr;
		});
		r->setTexture(this->_cameos[b]);
		if (!last.empty()) {
			std::string pos;

			pos.reserve(21 + 6);
			pos += "cameo_";
			pos += last;
			pos += ".y + cameo_";
			pos += last;
			pos += ".h";
			pic->setPosition({0, tgui::Layout{pos}});
		}
		last = b;
		this->_buildQueue->add(pic, "cameo_" + b);
		this->_buildQueueWidgets.push_back(pic);
	}
}

void SCBWUI::_createCameoUnitsWidgets()
{
	std::string last;

	for (size_t i = 0; i < this->_unitsOrder.size(); i++) {
		auto &b = this->_unitsOrder[i];
		std::string name = b.substr(b.find(':') + 1);
		auto pic = D2KCameo::create(this->_base);
		auto r = pic->getRenderer();

		pic->setSize(60, 48);
		pic->onMousePress([this, b, i]{
			this->_eventQueue.emplace_back(StartBuildEvent{b, *this->_unitsQueueEntries[i]->queueId});
		});
		pic->onRightMousePress([this, b, i]{
			this->_eventQueue.emplace_back(CancelBuildEvent{b, *this->_unitsQueueEntries[i]->queueId});
			this->_placementBuilding = nullptr;
		});
		r->setTexture(this->_cameos[b]);
		if (!last.empty()) {
			std::string pos;

			pos.reserve(21 + 6);
			pos += "cameo_";
			pos += last;
			pos += ".y + cameo_";
			pos += last;
			pos += ".h";
			pic->setPosition({0, tgui::Layout{pos}});
		}
		last = b;
		this->_unitsQueue->add(pic, "cameo_" + b);
		this->_unitsQueueWidgets.push_back(pic);
	}
}

void SCBWUI::_createCameoWidgets()
{
	this->_createCameoBuildWidgets();
	this->_createCameoUnitsWidgets();
}

SCBWUI::SCBWUI(const Faction &faction, UIState *state, GameManager *manager, PlayerState *ownerState, MapState *map, const std::filesystem::path &base, const nlohmann::json &params) :
	UI(faction, state, manager, ownerState, map),
	_prefix(params["cameo_prefix"]),
	_modName(faction.getBase().getName()),
	_base(base)
{
	faction.getBase().loadCursors("cursors.json", this->_cursors);

	this->_getPanelObjects(base / "ui" / game->locale / "ui.gui");
	this->_initPanel(params);
	this->_placeUiEvents();
	this->_loadExtraAssets();
	this->_loadCameos();
	this->_setupQueues();
	this->_loadEvaSounds(base, params["eva_folder"]);
	this->_setupCursorMapping();
	this->_createCameoWidgets();
}

SCBWUI::~SCBWUI() noexcept = default;

void SCBWUI::_updateQueueCameos()
{
	std::array orders = {
		std::tuple{&this->_buildOrder, &this->_buildingQueueEntries, &this->_buildQueueWidgets},
		std::tuple{&this->_unitsOrder, &this->_unitsQueueEntries, &this->_unitsQueueWidgets}
	};

	for (auto &order : orders)
		for (size_t i = 0; i < std::get<0>(order)->size(); i++) {
			PlayerQueueEntry *entry = (*std::get<1>(order))[i];
			D2KCameo::Ptr w = (*std::get<2>(order))[i];

			if (!entry || !entry->unlocked) {
				if (w->isVisible()) {
					w->setSize(60, 0);
					w->setVisible(false);
				}
				continue;
			}
			if (!w->isVisible()) {
				w->setVisible(true);
				w->setSize(60, 48);
			}
			w->setOnHold(entry->paused);
			if (!entry->buildable) {
				w->setFill(0);
				w->setReady(false);
			} else if (entry->buildProgress == 0) {
				w->setFill(1);
				w->setReady(false);
			} else if (entry->buildProgress >= entry->buildTime) {
				w->setFill(1);
				w->setReady(true);
			} else {
				w->setFill(entry->buildProgress / static_cast<float>(entry->buildTime));
				w->setReady(false);
			}
		}
}

void SCBWUI::update()
{
	UI::update();
	this->_minimapPos = this->_blazon->getPosition();
	this->_minimapSize = this->_blazon->getSize();
	if (this->ownerState->hasRadar) {
		this->_blazon->getRenderer()->setOpacity(0);
	} else {
		float opacity = this->_blazon->getRenderer()->getOpacity();

		opacity += 0.025;
		if (opacity >= 1)
			opacity = 1;
		this->_blazon->getRenderer()->setOpacity(opacity);
	}

	unsigned credits = std::min(99999999U, this->ownerState->getCombinedMoney("sc:mineral"));

	for (unsigned i = 0; i < 8; i++) {
		char m;

		if (credits != 0 || i == 0)
			m = credits % 10;
		else
			m = 10;
		if (this->_creditOldDigits[i] != m) {
			this->_creditDigits[i]->getRenderer()->setTexture(this->_creditRawDigits[m]);
			this->_creditOldDigits[i] = m;
		}
		credits /= 10;
	}
	this->_updateQueueCameos();

	float percent = 100 * (200.f + this->ownerState->producedPower) / (this->ownerState->consumedPower + 200.f);

	this->_power->setSize({10, percent});
	this->_greenPower->setVisible(percent >= 100);
	this->_yellowPower->setVisible(percent > 50 && percent < 100);
	this->_redPower->setVisible(percent <= 50);
}

void SCBWUI::render()
{
	UI::render();
	if (this->_dragging) {
		sf::VertexArray array{sf::PrimitiveType::LineStrip, 5};

		array[0].position.x = this->_startDrag->x;
		array[0].position.y = this->_startDrag->y;
		array[1].position.x = this->_startDrag->x;
		array[1].position.y = this->_placementPos.y;
		array[2].position.x = this->_placementPos.x;
		array[2].position.y = this->_placementPos.y;
		array[3].position.x = this->_placementPos.x;
		array[3].position.y = this->_startDrag->y;
		array[4].position.x = this->_startDrag->x;
		array[4].position.y = this->_startDrag->y;
		array[0].color = sf::Color{0xC5, 0xB6, 0xA4};
		array[1].color = sf::Color{0xC5, 0xB6, 0xA4};
		array[2].color = sf::Color{0xC5, 0xB6, 0xA4};
		array[3].color = sf::Color{0xC5, 0xB6, 0xA4};
		array[4].color = sf::Color{0xC5, 0xB6, 0xA4};
		game->screen->draw(array);
	}
}

void SCBWUI::playEVA(EVASound sound, unsigned int expireIn, unsigned int priority, unsigned int cooldown, const std::string &args)
{
	return;
	EVASound ignore[] = {
		EVA_MY_BUILDING_CAPTURED,
		EVA_MY_UNIT_CAPTURED,
		EVA_UNIT_CAPTURED,
		EVA_UNIT_ATTACKED,
		EVA_ALLIED_MY_BUILDING_CAPTURED,
		EVA_ALLIED_BUILDING_CAPTURED,
		EVA_ALLIED_BUILDING_ATTACKED,
		EVA_ALLIED_BUILDING_LOST,
		EVA_ALLIED_MY_UNIT_CAPTURED,
		EVA_ALLIED_UNIT_CAPTURED,
		EVA_ALLIED_UNIT_ATTACKED,
		EVA_ALREADY_BUILDING
	};

	if (std::ranges::find(ignore, sound) != std::end(ignore))
		return;
	if (sound == EVA_BUILDING) {
		if (args == this->_modName + ":upgrade")
			sound = EVA_UPGRADING;
		else if (args == this->_modName + ":infantry")
			sound = EVA_TRAINING;
	} else if (sound == EVA_BUILDING_DONE) {
		if (args == this->_modName + ":upgrade")
			// No built sound for upgrade queue
			return;
		if (args != this->_modName + ":building")
			sound = EVA_UNIT_READY;
		if (args == this->_modName + ":sabo")
			return;
		else if (args == this->_modName + ":frem")
			return;
		else if (args == this->_modName + ":orni")
			return;
		else if (args == this->_modName + ":dhmi")
			return;
	}
	UI::playEVA(sound, expireIn, priority, cooldown, args);
}

void SCBWUI::_displaySelectedObjectUI(const GameObject &object)
{
	auto select = object.getSelectBox();
	Vector2i size = select.size;
	Vector2i top = select.position;
	sf::Sprite sprite{this->_selectCorners[0]};
	sf::RectangleShape rect;

	top += object.getPosition();
	rect.setPosition({top.x + 1.f, top.y + 1.f});
	rect.setSize({size.x - 2.f, 2});
	rect.setOutlineThickness(1);
	rect.setOutlineColor(sf::Color::Black);
	rect.setFillColor(sf::Color{0, 0, 0, 128});
	game->screen->draw(rect);

	rect.setSize({(size.x - 2.f) * object.animationState.health, 2});
	if (object.animationState.health >= 0.5)
		rect.setFillColor(sf::Color::Green);
	else if (object.animationState.health >= 0.3)
		rect.setFillColor(sf::Color::Yellow);
	else
		rect.setFillColor(sf::Color::Red);
	game->screen->draw(rect);
	this->_displaySelectBox(top, size);
	top.y += 4;

	auto percent = object.getStorageDisplay();

	if (percent) {
		sf::Vector2f pos = {top.x + 2.f, top.y + size.y - 5.f};
		unsigned count = 7;

		if (size.x >= 64)
			count = 15;
		rect.setSize({2, 2});
		for (size_t i = 0; i < count; i++) {
			rect.setPosition(pos);
			if (*percent * count > i && percent != 0)
				rect.setFillColor(sf::Color{0, 255, 0, 255});
			else
				rect.setFillColor(sf::Color{0, 0, 0, 128});
			game->screen->draw(rect);
			pos.x += 3;
		}
	}
}
