//
// Created by PinkySmile on 07/10/2026.
//

#include "SCBWUI.hpp"

SL_DECLARE_VERSION;

SL_EXPORT UI *createUiFor(
	const Faction &faction,
	UIState *state,
	GameManager *manager,
	PlayerState *ownerState,
	MapState *map,
	const std::filesystem::path &base,
	const nlohmann::json &params
)
{
	return new SCBWUI(faction, state, manager, ownerState, map, base, params);
}
