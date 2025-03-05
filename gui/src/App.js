import React, { useState } from 'react';
import './App.css';
import PlayerCard from './components/PlayerCard';

const teams = {
  teamA: Array.from({ length: 10 }, (_, i) => ({
    id: `A${i + 1}`,
    name: `Игрок A${i + 1}`,
    firstName: `Иван ${i + 1}`,
    lastName: `Иванов ${i + 1}`,
    group: `Группа A${i + 1}`,
  })),
  teamB: Array.from({ length: 10 }, (_, i) => ({
    id: `B${i + 1}`,
    name: `Игрок B${i + 1}`,
    firstName: `Петр ${i + 1}`,
    lastName: `Петров ${i + 1}`,
    group: `Группа B${i + 1}`,
  })),
};

function App() {
  const [allFlipped, setAllFlipped] = useState(false);
  const [redCardId, setRedCardId] = useState(null);

  const handleHit = () => {
    // Устанавливаем первую карточку команды A как красную
    setRedCardId(teams.teamA[0].id);
  };

  const resetCards = () => {
    setRedCardId(null);
  };

  return (
    <div className="app">
      <h1>Военно-космическая академия имени А.Ф. Можайского</h1>

      <button className="flip-all-button" onClick={() => setAllFlipped(!allFlipped)}>
        {allFlipped ? 'Скрыть все' : 'Показать все'}
      </button>

      <div className="teams-container">
        <div className="team">
          <h2>Команда A</h2>
          <div className="player-list">
            {teams.teamA.map((player) => (
              <PlayerCard
                key={player.id}
                player={player}
                isRed={player.id === redCardId}
                allFlipped={allFlipped}
              />
            ))}
          </div>
        </div>
        <div className="team">
          <h2>Команда B</h2>
          <div className="player-list">
            {teams.teamB.map((player) => (
              <PlayerCard
                key={player.id}
                player={player}
                allFlipped={allFlipped}
              />
            ))}
          </div>
        </div>
      </div>

      {/* Кнопка сброса */}
      <button className="reset-button" onClick={resetCards}>
        Заново
      </button>

      {/* Кнопка Hit */}
      <button
        id="hit_but"
        onClick={handleHit}
        //style={{ display: 'none' }} // Исправлено: добавлены фигурные скобки
      >
        БОЙ
      </button>
    </div>
  );
}

export default App;