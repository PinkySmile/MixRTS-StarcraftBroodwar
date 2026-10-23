//
// Created by PinkySmile on 31/03/2026.
//

#ifndef MIXRTS_D2KCAMEO_HPP
#define MIXRTS_D2KCAMEO_HPP


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <TGUI/Renderers/WidgetRenderer.hpp>
#include <TGUI/Widgets/ClickableWidget.hpp>
#include "Sprite.hpp"

class D2KCameo : public tgui::ClickableWidget {
public:
	class Renderer : public tgui::WidgetRenderer {
	public:
		using WidgetRenderer::WidgetRenderer;

		void setTexture(const tgui::Texture &texture);
		const tgui::Texture& getTexture() const;
		const tgui::Texture& getBnWTexture() const;
	};

	using Ptr = std::shared_ptr<D2KCameo>; //!< Shared widget pointer
	using ConstPtr = std::shared_ptr<const D2KCameo>; //!< Shared constant widget pointer

	D2KCameo(const std::filesystem::path &base, const char *typeName = StaticWidgetType, bool initRenderer = true);

	Renderer *getSharedRenderer() override;
	const Renderer *getSharedRenderer() const override;
	Renderer *getRenderer() override;

	static constexpr const char StaticWidgetType[] = "D2KCameo"; //!< Type name of the widget

	void setCount(std::optional<unsigned> count);
	float getFill() const;
	void setFill(float fill);
	bool isOnHold() const;
	void setOnHold(bool onHold);
	bool isReady() const;
	void setReady(bool ready);
	void draw(tgui::BackendRenderTarget &target, tgui::RenderStates states) const override;
	void setSize(const tgui::Layout2d &size) override;
        using Widget::setSize;
	[[nodiscard]] bool isMouseOnWidget(tgui::Vector2f pos) const override;
	Widget::Ptr clone() const override;
	bool updateTime(tgui::Duration elapsedTime) override;

	static Ptr create(const std::filesystem::path &base);
	static Ptr create(const std::filesystem::path &base, const tgui::Texture &texture);
	static Ptr copy(const ConstPtr &picture);

protected:
	void rendererChanged(const tgui::String &property) override;
	void _computeFillVertices();

	bool _hold = false;
	bool _ready = false;
	float _fill = 0;
	unsigned _timer = 0;
	std::optional<unsigned> _count;
	tgui::Sprite _sprite;
	Sprite _spriteHold;
	Sprite _spriteReady;
	sf::Texture _bnwTexture;
	sf::Text _text;
	sf::VertexArray _vertices{sf::PrimitiveType::TriangleFan, 0};
};



#endif //MIXRTS_D2KCAMEO_HPP
