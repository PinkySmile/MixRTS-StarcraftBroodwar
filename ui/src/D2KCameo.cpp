//
// Created by PinkySmile on 31/03/2026.
//

#include <cmath>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <TGUI/Backend/Renderer/SFML-Graphics/BackendRenderTargetSFML.hpp>
#include <TGUI/Container.hpp>
#include "D2KCameo.hpp"
#include "Resources/Assert.hpp"
#include "Resources/Game.hpp"

D2KCameo::D2KCameo(const std::filesystem::path &base, const char *typeName, bool initRenderer) :
	ClickableWidget{typeName, false},
	_text(game->font)
{
	if (initRenderer) {
		this->m_renderer = aurora::makeCopied<Renderer>();
		setRenderer(tgui::Theme::getDefault()->getRendererNoThrow(this->m_type));
	}

	this->_spriteReady.load(base / "ui" / game->locale / "ready.png", nullptr, false, true);
	this->_spriteReady.setPosition({1, 1});
	this->_spriteHold.load(base / "ui" / game->locale / "hold.png", nullptr, false, true);

	this->_text.setCharacterSize(10);
	this->_text.setPosition({2, 2});
	this->_text.setOutlineColor(sf::Color::Black);
	this->_text.setOutlineThickness(1);
}

void D2KCameo::Renderer::setTexture(const tgui::Texture &texture)
{
	auto data = texture.getData();
	tgui::Texture t;
	const tgui::Texture *toUse = &texture;

	if (!data) {
		sf::Image img{sf::Vector2u{60, 47}};

		for (size_t y = 1; y < 46; y++)
			for (size_t x = 1; x < 59; x++)
				img.setPixel({static_cast<unsigned int>(x), static_cast<unsigned int>(y)}, {static_cast<uint8_t>(rand()), static_cast<uint8_t>(rand()), static_cast<uint8_t>(rand()), 255});
		t.loadFromPixelData(img.getSize(), img.getPixelsPtr());
		toUse = &t;
	}

	setProperty(tgui::String("Texture"), {*toUse});

	tgui::Texture bnw;
	auto tex = toUse->getData()->backendTexture;
	auto size = tex->getSize();
	auto ptr = tex->getPixels();
	std::vector<uint8_t> pixels{ptr, ptr + size.x * size.y * 4};

	for (size_t i = 0; i < size.x * size.y * 4; i += 4) {
		pixels[i + 1] = pixels[i + 1] * 3 / 4;
		pixels[i + 0] = pixels[i + 1];
		pixels[i + 2] = pixels[i + 1];
	}
	bnw.loadFromPixelData(size, pixels.data());
	setProperty(tgui::String("BnWTexture"), {bnw});
}

const tgui::Texture &D2KCameo::Renderer::getTexture() const
{
	const auto it = this->m_data->propertyValuePairs.find("Texture");

	if (it != this->m_data->propertyValuePairs.end())
		return it->second.getTexture();
	this->m_data->propertyValuePairs["Texture"] = {tgui::Texture{}};
	return this->m_data->propertyValuePairs["Texture"].getTexture();
}

const tgui::Texture &D2KCameo::Renderer::getBnWTexture() const
{
	const auto it = this->m_data->propertyValuePairs.find("BnWTexture");

	if (it != this->m_data->propertyValuePairs.end())
		return it->second.getTexture();
	this->m_data->propertyValuePairs["BnWTexture"] = {tgui::Texture{}};
	return this->m_data->propertyValuePairs["BnWTexture"].getTexture();
}

D2KCameo::Renderer *D2KCameo::getSharedRenderer()
{
	return aurora::downcast<Renderer *>(Widget::getSharedRenderer());
}

const D2KCameo::Renderer *D2KCameo::getSharedRenderer() const
{
	return aurora::downcast<const Renderer *>(Widget::getSharedRenderer());
}

D2KCameo::Renderer *D2KCameo::getRenderer()
{
	return aurora::downcast<Renderer *>(Widget::getRenderer());
}

void D2KCameo::setCount(std::optional<unsigned> count)
{
	this->_count = count;
	if (count)
		this->_text.setString(std::to_string(*this->_count));
}

float D2KCameo::getFill() const
{
	return this->_fill;
}

void D2KCameo::setFill(float fill)
{
	if (fill == this->_fill)
		return;
	this->_fill = fill;
	this->_computeFillVertices();
}

bool D2KCameo::isOnHold() const
{
	return this->_hold;
}

void D2KCameo::setOnHold(bool onHold)
{
	this->_hold = onHold;
}

bool D2KCameo::isReady() const
{
	return this->_ready;
}

void D2KCameo::setReady(bool ready)
{
	this->_ready = ready;
}

void D2KCameo::_computeFillVertices()
{
	if (this->_fill == 0)
		return this->_vertices.clear();

	unsigned quadrants = std::floor(this->_fill / 0.125) + 1;
	auto size = this->getSize();

	this->_vertices.resize(quadrants + 2);
	this->_vertices[0].position.x = size.x / 2;
	this->_vertices[0].position.y = size.y / 2;
	this->_vertices[0].texCoords.x = 0.5;
	this->_vertices[0].texCoords.y = 0.5;
	this->_vertices[1].position.x = size.x / 2;
	this->_vertices[1].position.y = 0;
	this->_vertices[1].texCoords.x = 0.5;
	this->_vertices[1].texCoords.y = 0;
	for (size_t i = 0; i < quadrants; i++) {
		sf::Vector2f qSize;

		switch (i) {
		case 0:
		case 7:
			qSize = {0.5, 0};
			break;
		case 1:
		case 2:
			qSize = {0, 0.5};
			break;
		case 3:
		case 4:
			qSize = {-0.5, 0};
			break;
		case 5:
		case 6:
			qSize = {0, -0.5};
			break;
		}
		if (i == quadrants - 1) {
			float fillTotal = fmod(this->_fill, 0.125) * 8;

			qSize.x *= fillTotal;
			qSize.y *= fillTotal;
		}
		this->_vertices[2 + i].position = this->_vertices[1 + i].position + sf::Vector2f{qSize.x * size.x, qSize.y * size.y};
		this->_vertices[2 + i].texCoords = this->_vertices[1 + i].texCoords + sf::Vector2f{qSize.x, qSize.y};
	}
}

void D2KCameo::draw(tgui::BackendRenderTarget &target, tgui::RenderStates states) const
{
	checked_cast(sfmlTarget, tgui::BackendRenderTargetSFML, &target);
	target.drawSprite(states, this->_sprite);
	const std::array<float, 16> &transformMatrix = states.transform.getMatrix();
	sf::RenderStates statesSFML;
	auto realTarget = sfmlTarget->getTarget();

	statesSFML.transform = sf::Transform(
		transformMatrix[0], transformMatrix[4], transformMatrix[12],
		transformMatrix[1], transformMatrix[5], transformMatrix[13],
		transformMatrix[3], transformMatrix[7], transformMatrix[15]
	);
	statesSFML.coordinateType = sf::CoordinateType::Normalized;
	statesSFML.texture = &this->_bnwTexture;
	realTarget->draw(this->_vertices, statesSFML);

	statesSFML.texture = nullptr;
	if (this->_hold)
		realTarget->draw(this->_spriteHold, statesSFML);
	else if (this->_ready)
		realTarget->draw(this->_spriteReady, statesSFML);
	if (this->_count)
		realTarget->draw(this->_text, statesSFML);
}

bool D2KCameo::updateTime(tgui::Duration elapsedTime)
{
	this->_timer += elapsedTime.asSeconds() * 1000;
	if (this->_timer >= 500)
		this->_timer -= 500;
	this->_spriteReady.setColor({
		0xFF,
		static_cast<uint8_t>(0xFF - (96 - this->_timer * 96 / 1000)),
		0xFF,
		0xFF
	});
	this->_spriteHold.setColor(this->_spriteReady.getColor());
	return ClickableWidget::updateTime(elapsedTime);
}

void D2KCameo::setSize(const tgui::Layout2d &size)
{
	Widget::setSize(size);
	this->_sprite.setSize(this->getSize());
	this->_computeFillVertices();
}

bool D2KCameo::isMouseOnWidget(tgui::Vector2f pos) const
{
	return tgui::FloatRect{0, 0, getSize().x, getSize().y}.contains(pos - getPosition());
}

void D2KCameo::rendererChanged(const tgui::String &property)
{
	if (property == U"Texture") {
		const auto &texture = this->getSharedRenderer()->getTexture();

		if (
			!this->_sprite.isSet() &&
			this->m_size.x.isConstant() && this->m_size.y.isConstant() &&
			this->getSize() == tgui::Vector2f{0, 0}
		)
			this->setSize(tgui::Vector2f{texture.getImageSize()});

		auto data = texture.getData();
		auto tex = data->backendTexture;
		sf::Image img{tex->getSize(), tex->getPixels()};

		assert_exp(this->_bnwTexture.loadFromImage(img));
		this->_bnwTexture.setSmooth(texture.isSmooth());
		this->_computeFillVertices();
	} else if (property == U"BnWTexture") {
		this->_sprite.setTexture(this->getSharedRenderer()->getBnWTexture());
	}
}

tgui::Widget::Ptr D2KCameo::clone() const
{
	return std::make_shared<D2KCameo>(*this);
}

D2KCameo::Ptr D2KCameo::create(const std::filesystem::path &base)
{
	return std::make_shared<D2KCameo>(base);
}

D2KCameo::Ptr D2KCameo::create(const std::filesystem::path &base, const tgui::Texture &texture)
{
	auto picture = std::make_shared<D2KCameo>(base);

	picture->getRenderer()->setTexture(texture);
	return picture;
}

D2KCameo::Ptr D2KCameo::copy(const ConstPtr &picture)
{
	if (picture)
		return std::static_pointer_cast<D2KCameo>(picture->clone());
	return nullptr;
}
