#include "Public/GameEngine.h"
#include "Public/GameRenderer.h"
#include "Board.h"

Board::~Board()
{
	for (auto& Texture : BlockTextureCache)
	{
		Texture.second.reset();
		Texture.second = nullptr;
	}
}

Board::Board(Board&& InInstance) noexcept
	: BoardWidth(InInstance.BoardWidth)
	, BoardHeight(InInstance.BoardHeight)
	, BoardState(InInstance.BoardState)
{
}

Board::Board(const Board& InInstance) noexcept
	: BoardWidth(InInstance.BoardWidth)
	, BoardHeight(InInstance.BoardHeight)
	, BoardState(InInstance.BoardState)
{
}

Board& Board::operator=(Board&& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	BoardWidth  = InInstance.BoardWidth;
	BoardHeight = InInstance.BoardHeight;
	BoardState  = InInstance.BoardState;

	return *this;
}

Board& Board::operator=(const Board& InInstance) noexcept
{
	if (this == &InInstance) return *this;

	BoardWidth  = InInstance.BoardWidth;
	BoardHeight = InInstance.BoardHeight;
	BoardState  = InInstance.BoardState;

	return *this;
}

void Board::Init(int32_t InBoardWidth, int32_t InBoardHeight)
{
	BoardWidth  = InBoardWidth;
	BoardHeight = InBoardHeight;

	Reset();

	if (BlockTextureCache.empty())
	{
		CreateBlockTexture();
	}
}

void Board::Reset()
{
	BoardState.resize(BoardWidth * BoardHeight, Block(EBlockState::EMPTY, EBlockColor::GRAY));

	for (int32_t Row = 0; Row < BoardHeight; ++Row)
	{
		if (Row == BoardHeight - 1)
		{
			for (int32_t Col = 0; Col < BoardWidth; ++Col)
			{
				BoardState[GetBoardOffset(Row, Col)] = Block(EBlockState::FIX, EBlockColor::GRAY);
			}
		}
		else
		{
			BoardState[GetBoardOffset(Row, 0)]              = Block(EBlockState::FIX, EBlockColor::GRAY);
			BoardState[GetBoardOffset(Row, BoardWidth - 1)] = Block(EBlockState::FIX, EBlockColor::GRAY);
		}
	}
}

Block Board::GetBlockInBoard(int32_t InRow, int32_t InCol) const
{
	CHECK_FAILED(IsInsidePosition(InRow, InCol), "out of range in board");
	return BoardState[GetBoardOffset(InRow, InCol)];
}

EBlockState Board::GetBlockStateInBoard(int32_t InRow, int32_t InCol) const
{
	return GetBlockInBoard(InRow, InCol).first;
}

EBlockColor Board::GetBlockColorInBoard(int32_t InRow, int32_t InCol) const
{
	return GetBlockInBoard(InRow, InCol).second;
}

void Board::SetBlockInBoard(int32_t InRow, int32_t InCol, const Block& InBlock)
{
	if (IsInsidePosition(InRow, InCol))
	{
		BoardState[GetBoardOffset(InRow, InCol)] = InBlock;
	}
}

void Board::SetBlockStateInBoard(int32_t InRow, int32_t InCol, const EBlockState& InBlockState)
{
	if (IsInsidePosition(InRow, InCol))
	{
		BoardState[GetBoardOffset(InRow, InCol)].first = InBlockState;
	}
}

void Board::SetBlockColorInBoard(int32_t InRow, int32_t InCol, const EBlockColor& InBlockColor)
{
	if (IsInsidePosition(InRow, InCol))
	{
		BoardState[GetBoardOffset(InRow, InCol)].second = InBlockColor;
	}
}

void Board::DrawBoard(const Vec2i& InPosition, float InScale)
{
	for (int32_t Row = 0; Row < BoardHeight; ++Row)
	{
		for (int32_t Col = 0; Col < BoardWidth; ++Col)
		{
			if (GetBlockStateInBoard(Row, Col) != EBlockState::EMPTY)
			{
				int32_t TextureWidth = 0, TextureHeight = 0;

				TextureWidth = static_cast<int32_t>(static_cast<float>(
					BlockTextureCache[GetBlockColorInBoard(Row, Col)]->GetWidth()) * InScale
					);

				TextureHeight = static_cast<int32_t>(static_cast<float>(
					BlockTextureCache[GetBlockColorInBoard(Row, Col)]->GetWidth()) * InScale
					);


				Vec2i MovePosition(Col * TextureWidth, Row * TextureHeight);


				GameEngine::GetGameRenderer().DrawTexture2D(
					*BlockTextureCache[GetBlockColorInBoard(Row, Col)].get(),
					InPosition + MovePosition,
					InScale,
					InScale
				);
			}
		}
	}
}

bool Board::IsInsidePosition(int32_t InRow, int32_t InCol) const
{
	return (0 <= InRow && InRow < BoardHeight) 
		&& (0 <= InCol && InCol < BoardWidth);
}

int32_t Board::GetBoardOffset(int32_t InRow, int32_t InCol) const
{
	return InRow * BoardWidth + InCol;
}

void Board::CreateBlockTexture()
{
	std::string ResourceDirectory = GameEngine::GetResourceDirectory();

	std::vector<std::pair<EBlockColor, std::string>> BlockInfos = {
		{ EBlockColor::BLUE,   "BlueBlock"   },
		{ EBlockColor::CYAN,   "CyanBlock"   },
		{ EBlockColor::GRAY,   "GrayBlock"   },
		{ EBlockColor::GREEN,  "GreenBlock"  },
		{ EBlockColor::ORANGE, "OrangeBlock" },
		{ EBlockColor::PINK,   "PinkBlock"   },
		{ EBlockColor::PURPLE, "PurpleBlock" },
		{ EBlockColor::RED,    "RedBlock"    },
		{ EBlockColor::YELLOW, "YellowBlock" }
	};

	for (const auto& BlockInfo : BlockInfos)
	{
		std::string TexturePath = StringUtil::StringFormat(
			"%stexture/%s.png",
			ResourceDirectory.c_str(),
			BlockInfo.second.c_str()
		);

		BlockTextureCache[BlockInfo.first] = std::make_unique<GameTexture2D>();
		BlockTextureCache[BlockInfo.first].get()->CreateTextureFromFile(TexturePath);
	}
}
